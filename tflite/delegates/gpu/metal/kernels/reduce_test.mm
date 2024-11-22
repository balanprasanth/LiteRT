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

#import <XCTest/XCTest.h>

#include "tflite/delegates/gpu/common/status.h"
#include "tflite/delegates/gpu/common/tasks/reduce_test_util.h"
#include "tflite/delegates/gpu/metal/kernels/test_util.h"

@interface ReduceTest : XCTestCase
@end

@implementation ReduceTest {
  tflite::gpu::metal::MetalExecutionEnvironment exec_env_;
}

- (void)testMeanHW {
  auto status = MeanHWTest(&exec_env_);
  XCTAssertTrue(status.ok(), @"%s", std::string(status.message()).c_str());
}

- (void)testReduceSumChannels {
  auto status = ReduceSumChannelsTest(&exec_env_);
  XCTAssertTrue(status.ok(), @"%s", std::string(status.message()).c_str());
}

- (void)testReduceProductChannels {
  auto status = ReduceProductChannelsTest(&exec_env_);
  XCTAssertTrue(status.ok(), @"%s", std::string(status.message()).c_str());
}

- (void)testReduceMaxChannels {
  auto status = ReduceMaxChannelsTest(&exec_env_);
  XCTAssertTrue(status.ok(), @"%s", std::string(status.message()).c_str());
}

- (void)testReduceMinChannels {
  auto status = ReduceMinChannelsTest(&exec_env_);
  XCTAssertTrue(status.ok(), @"%s", std::string(status.message()).c_str());
}

@end
