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

#ifndef TENSORFLOW_LITE_DELEGATES_GPU_COMMON_TRANSFORMATIONS_MAKE_PADDING_H_
#define TENSORFLOW_LITE_DELEGATES_GPU_COMMON_TRANSFORMATIONS_MAKE_PADDING_H_

#include <memory>

#include "tflite/delegates/gpu/common/model_transformer.h"

namespace tflite {
namespace gpu {

// Turns concat that handles only two tensors, where one tensor is zeros, into
// padding operation.
std::unique_ptr<NodeTransformation> NewMakePaddingFromConcat();

}  // namespace gpu
}  // namespace tflite

#endif  // TENSORFLOW_LITE_DELEGATES_GPU_COMMON_TRANSFORMATIONS_MAKE_PADDING_H_
