/* Copyright 2021 The TensorFlow Authors. All Rights Reserved.

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

#include <cstdint>
#include <functional>
#include <limits>
#include <memory>
#include <random>

#include <gtest/gtest.h>
#include "tflite/delegates/xnnpack/quantized_unary_elementwise_tester.h"
#include "tflite/delegates/xnnpack/xnnpack_delegate.h"

namespace tflite {
namespace xnnpack {

TEST(UnsignedQuantizedLogistic, 4D) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto shape_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  const auto batch = shape_rng();
  const auto height = shape_rng();
  const auto width = shape_rng();
  const auto channels = shape_rng();

  QuantizedUnaryElementwiseTester()
      .Unsigned(true)
      .Shape({batch, height, width, channels})
      .InputZeroPoint(127)
      .InputScale(15.0f / 127.0f)
      .OutputZeroPoint(std::numeric_limits<uint8_t>::min())
      .OutputScale(1.0f / 256.0f)
      .Test(BuiltinOperator_LOGISTIC, xnnpack_delegate.get());
}

TEST(UnsignedQuantizedLogistic, 3D) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto shape_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  const auto batch = shape_rng();
  const auto width = shape_rng();
  const auto channels = shape_rng();

  QuantizedUnaryElementwiseTester()
      .Unsigned(true)
      .Shape({batch, width, channels})
      .InputZeroPoint(127)
      .InputScale(15.0f / 127.0f)
      .OutputZeroPoint(std::numeric_limits<uint8_t>::min())
      .OutputScale(1.0f / 256.0f)
      .Test(BuiltinOperator_LOGISTIC, xnnpack_delegate.get());
}

TEST(UnsignedQuantizedLogistic, 2D) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto shape_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  const auto batch = shape_rng();
  const auto channels = shape_rng();

  QuantizedUnaryElementwiseTester()
      .Unsigned(true)
      .Shape({batch, channels})
      .InputZeroPoint(127)
      .InputScale(15.0f / 127.0f)
      .OutputZeroPoint(std::numeric_limits<uint8_t>::min())
      .OutputScale(1.0f / 256.0f)
      .Test(BuiltinOperator_LOGISTIC, xnnpack_delegate.get());
}

TEST(UnsignedQuantizedLogistic, 1D) {
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(nullptr),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto shape_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  const auto batch = shape_rng();

  QuantizedUnaryElementwiseTester()
      .Unsigned(true)
      .Shape({batch})
      .InputZeroPoint(127)
      .InputScale(15.0f / 127.0f)
      .OutputZeroPoint(std::numeric_limits<uint8_t>::min())
      .OutputScale(1.0f / 256.0f)
      .Test(BuiltinOperator_LOGISTIC, xnnpack_delegate.get());
}

TEST(UnsignedQuantizedLogistic, MultiThreading) {
  TfLiteXNNPackDelegateOptions delegate_options =
      TfLiteXNNPackDelegateOptionsDefault();
  delegate_options.num_threads = 2;
  std::unique_ptr<TfLiteDelegate, decltype(&TfLiteXNNPackDelegateDelete)>
      xnnpack_delegate(TfLiteXNNPackDelegateCreate(&delegate_options),
                       TfLiteXNNPackDelegateDelete);

  std::random_device random_device;
  auto rng = std::mt19937(random_device());
  auto shape_rng =
      std::bind(std::uniform_int_distribution<int32_t>(2, 5), std::ref(rng));
  const auto batch = shape_rng();
  const auto height = shape_rng();
  const auto width = shape_rng();
  const auto channels = shape_rng();

  QuantizedUnaryElementwiseTester()
      .Unsigned(true)
      .Shape({batch, height, width, channels})
      .InputZeroPoint(127)
      .InputScale(15.0f / 127.0f)
      .OutputZeroPoint(std::numeric_limits<uint8_t>::min())
      .OutputScale(1.0f / 256.0f)
      .Test(BuiltinOperator_LOGISTIC, xnnpack_delegate.get());
}

}  // namespace xnnpack
}  // namespace tflite
