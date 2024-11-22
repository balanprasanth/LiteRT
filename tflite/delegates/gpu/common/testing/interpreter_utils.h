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

#ifndef TENSORFLOW_LITE_DELEGATES_GPU_COMMON_TESTING_INTERPRETER_UTILS_H_
#define TENSORFLOW_LITE_DELEGATES_GPU_COMMON_TESTING_INTERPRETER_UTILS_H_

#include <vector>

#include "tflite/core/api/op_resolver.h"
#include "tflite/core/c/common.h"
#include "tflite/delegates/gpu/common/status.h"
#include "tflite/delegates/gpu/common/tensor.h"
#include "tflite/schema/schema_generated.h"

namespace tflite {
namespace gpu {
namespace testing {

// Runs Tensorflow Lite model using Tensorflow Lite with a delegate and
// an appropriate operations resolver. If delegate is nullptr, inference will
// be done only on CPU.
absl::Status InterpreterInvokeWithOpResolver(
    const ::tflite::Model* model, TfLiteDelegate* delegate,
    const OpResolver& op_resolver, const std::vector<TensorFloat32>& inputs,
    std::vector<TensorFloat32>* outputs);

// Runs Tensorflow Lite model using Tensorflow Lite with a delegate and
// builtin operations resolver. If delegate is nullptr, inference will
// be done only on CPU.
absl::Status InterpreterInvoke(const ::tflite::Model* model,
                               TfLiteDelegate* delegate,
                               const std::vector<TensorFloat32>& inputs,
                               std::vector<TensorFloat32>* outputs);

}  // namespace testing
}  // namespace gpu
}  // namespace tflite

#endif  // TENSORFLOW_LITE_DELEGATES_GPU_COMMON_TESTING_INTERPRETER_UTILS_H_
