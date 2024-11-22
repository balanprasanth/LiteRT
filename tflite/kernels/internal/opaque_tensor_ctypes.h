/* Copyright 2023 The TensorFlow Authors. All Rights Reserved.

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
#ifndef TENSORFLOW_LITE_KERNELS_INTERNAL_OPAQUE_TENSOR_CTYPES_H_
#define TENSORFLOW_LITE_KERNELS_INTERNAL_OPAQUE_TENSOR_CTYPES_H_

#include "tflite/c/c_api_opaque.h"
#include "tflite/core/macros.h"
#include "tflite/kernels/internal/types.h"
#include "tflite/namespace.h"

namespace tflite {
namespace TFLITE_CONDITIONAL_NAMESPACE {

/// Returns the dimensions of the given tensor.
TFLITE_NOINLINE RuntimeShape GetTensorShape(const TfLiteOpaqueTensor* tensor);

}  // namespace TFLITE_CONDITIONAL_NAMESPACE

using ::tflite::TFLITE_CONDITIONAL_NAMESPACE::GetTensorShape;

}  // namespace tflite

#endif  // TENSORFLOW_LITE_KERNELS_INTERNAL_OPAQUE_TENSOR_CTYPES_H_
