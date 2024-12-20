// Copyright 2024 Google LLC.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <string>
#include <utility>

#include "absl/strings/str_format.h"
#include "tflite/experimental/litert/c/litert_common.h"
#include "tflite/experimental/litert/c/litert_model.h"
#include "tflite/experimental/litert/cc/litert_macros.h"
#include "tflite/experimental/litert/cc/litert_model.h"
#include "tflite/experimental/litert/vendors/c/litert_compiler_plugin.h"
#include "tflite/experimental/litert/vendors/cc/conversion.h"
#include "tflite/experimental/litert/vendors/cc/partition_with_capabilities.h"
#include "tflite/experimental/litert/vendors/examples/example_conversion_impl.h"
#include "tflite/experimental/litert/vendors/examples/example_ir.h"
#include "tflite/experimental/litert/vendors/examples/example_plugin_common.h"

using ::litert::PartitionWithCapabilities;
using ::litert::example::ExampleGraphBuilder;
using ::litert::example::ExampleOpAllocator;
using ::litert::example::ExampleOpType;
using ::litert::example::ExampleTensorAllocator;
using ::litert::example::ExampleTypes;
using ::litert::example::MakeAllLegalizations;
using ::litert::example::MakeTensorConverter;

// Example plugin implementations that leverage the pluggable conversion
// infrastructure. Implementations of common interfaces are provided in
// example_conversion_impl.h. These are passed to higher-level litert functions
// to perform the actual conversion.
// The primary benifit of this approach is the re-use of conversion logic
// between the partition and compile phases.
// TODO: Update with graph conversion function.

// Plugins can hold state.
struct LiteRtCompilerPluginT {
  ExampleTypes::Legalizations legalizations;
};

namespace {

bool MulCapability(const ExampleTypes::Op* op) {
  return op->op_code == ExampleOpType::MUL;
}

}  // namespace

// Initialize example plugin and register legalizations.
LiteRtStatus LiteRtCreateCompilerPlugin(LiteRtCompilerPlugin* compiler_plugin) {
  auto* plugin = new LiteRtCompilerPluginT;
  plugin->legalizations = MakeAllLegalizations();
  *compiler_plugin = plugin;
  return kLiteRtStatusOk;
}

void LiteRtDestroyCompilerPlugin(LiteRtCompilerPlugin compiler_plugin) {
  delete compiler_plugin;
}

// Leverage the convert_type PartitionViaCapabilties algorithm for partitioning
// implementation.
LiteRtStatus LiteRtCompilerPluginPartition(LiteRtCompilerPlugin compiler_plugin,
                                           LiteRtSubgraph subgraph,
                                           LiteRtOpList selected_ops) {
  ExampleTensorAllocator tensor_alloc;
  ExampleOpAllocator op_alloc;

  auto ops = PartitionWithCapabilities<ExampleTypes>(
      compiler_plugin->legalizations, MulCapability, MakeTensorConverter,
      tensor_alloc, op_alloc, ::litert::Subgraph(subgraph));
  if (!ops) {
    return ops.Error().Status();
  }

  for (auto* op : *ops) {
    LITERT_RETURN_STATUS_IF_NOT_OK(LiteRtPushOp(selected_ops, op));
  }

  return kLiteRtStatusOk;
}

namespace {

// TODO: Pull common graph conversion stuff into public function.
LiteRtStatus CompileSinglePartition(
    const ExampleTypes::Legalizations& legalizations, std::string name,
    LiteRtSubgraph subgraph, LiteRtCompiledResultT& result) {
  ExampleGraphBuilder builder;

  // Wrap tensor converters so legaizations can hook into the graph builder.
  auto make_tensor_converter = [&builder](auto alloc) {
    return [alloc, &builder](const auto& litert_tensor) {
      auto converter = MakeTensorConverter(alloc);
      auto tensor = converter(litert_tensor);
      if (!tensor) {
        return tensor;
      }
      builder.RegisterTensor(**tensor);
      return tensor;
    };
  };

  builder.InitGraph(name);

  const litert::Subgraph sg(subgraph);
  auto map = ExampleTypes::MakeLegalizationMap(legalizations);

  ExampleTensorAllocator tensor_alloc;
  ExampleOpAllocator op_alloc;

  for (const auto& op : sg.Ops()) {
    auto it = map.find(op.Code());
    if (it == map.end()) {
      return kLiteRtStatusErrorUnsupported;
    }

    auto result =
        it->second->Legalize(op, make_tensor_converter, make_tensor_converter,
                             tensor_alloc, op_alloc);
    if (!result) {
      return result.Error().Status();
    }

    auto simple_result = litert::GetSimpleConversionResult(*result);
    if (!simple_result) {
      return simple_result.Error().Status();
    }

    LITERT_RETURN_STATUS_IF_NOT_OK(builder.RegisterOp(**simple_result));
  }

  builder.FinalizeGraph();
  result.byte_code.append(builder.Serialize());
  result.per_op_data.push_back(std::move(name));

  return kLiteRtStatusOk;
}

}  // namespace

// Plugin compiler implementation that leverages the pluggable convert_types
// infrastructure.
LiteRtStatus LiteRtCompilerPluginCompile(
    LiteRtCompilerPlugin compiler_plugin, const char* soc_model,
    LiteRtSubgraph* partitions, LiteRtParamIndex num_partitions,
    LiteRtCompiledResult* compiled_result) {
  auto* result = new LiteRtCompiledResultT;

  for (auto i = 0; i < num_partitions; ++i) {
    auto name = absl::StrFormat("partition_%lu", i);
    LITERT_RETURN_STATUS_IF_NOT_OK(
        CompileSinglePartition(compiler_plugin->legalizations, std::move(name),
                               partitions[i], *result));
  }

  *compiled_result = result;

  return kLiteRtStatusOk;
}
