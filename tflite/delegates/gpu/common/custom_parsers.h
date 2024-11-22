/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/
#ifndef TENSORFLOW_LITE_DELEGATES_GPU_COMMON_CUSTOM_PARSERS_H_
#define TENSORFLOW_LITE_DELEGATES_GPU_COMMON_CUSTOM_PARSERS_H_

#include <cstdint>
#include <memory>

#include "absl/strings/string_view.h"
#include "absl/types/any.h"
#include "tflite/delegates/gpu/common/operation_parser.h"
#include "tflite/delegates/gpu/common/shape.h"
#include "tflite/delegates/gpu/common/status.h"

namespace tflite {
namespace gpu {

// Returns a parser for the provided custom op.
std::unique_ptr<TFLiteOperationParser> NewCustomOperationParser(
    absl::string_view op_name);

}  // namespace gpu
}  // namespace tflite

#endif  // TENSORFLOW_LITE_DELEGATES_GPU_COMMON_CUSTOM_PARSERS_H_
