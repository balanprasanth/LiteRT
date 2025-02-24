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

#include "third_party/odml/litert/litert/vendors/qualcomm/compiler/legalizations/div_op_legalization.h"

#include <string>

#include "third_party/absl/strings/str_format.h"
#include "third_party/absl/strings/string_view.h"
#include "third_party/odml/litert/litert/c/litert_common.h"
#include "third_party/odml/litert/litert/c/litert_op_code.h"
#include "third_party/odml/litert/litert/cc/litert_expected.h"
#include "third_party/odml/litert/litert/cc/litert_macros.h"
#include "third_party/odml/litert/litert/cc/litert_model.h"
#include "third_party/odml/litert/litert/vendors/qualcomm/compiler/graph_mapper.h"
#include "third_party/odml/litert/litert/vendors/qualcomm/compiler/legalizations/util.h"
#include "third_party/qairt/latest/include/QNN/QnnTypes.h"

namespace litert::qnn {

static constexpr absl::string_view kQnnDivOpTypeName = "ElementWiseDivide";
static constexpr absl::string_view kDefaultQnnOpPackageName = "qti.aisw";
static constexpr absl::string_view kDivOpFmt = "div_%d";

LiteRtStatus DivOpLegalization::LegalizeOp(const litert::Op& src,
                                           Qnn_OpConfig_t& dest,
                                           GraphMapper& graph_mapper) {
  if (src.Code() != kLiteRtOpCodeTflDiv) {
    return kLiteRtStatusLegalizeNoMatch;
  }
  std::string op_name = absl::StrFormat(kDivOpFmt, op_counter_++);
  LITERT_RETURN_IF_ERROR(SetOpInfo(op_name.c_str(),
                                   kDefaultQnnOpPackageName.data(),
                                   kQnnDivOpTypeName.data(), dest));
  LITERT_RETURN_IF_ERROR(LegalizeSimpleOp(src, dest, graph_mapper));
  LITERT_LOG(LITERT_INFO, "Legalized div op", "");
  return kLiteRtStatusOk;
}

}  // namespace litert::qnn
