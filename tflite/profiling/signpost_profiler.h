/* Copyright 2020 The TensorFlow Authors. All Rights Reserved.

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
#ifndef TENSORFLOW_LITE_PROFILING_SIGNPOST_PROFILER_H_
#define TENSORFLOW_LITE_PROFILING_SIGNPOST_PROFILER_H_

#include <memory>

#include "tflite/core/api/profiler.h"

namespace tflite {
namespace profiling {

// Creates a platform profiler for iOS, macOS, tvOS and watchOS.
// This profiler uses Apple's signpost API for tracing events.
// User needs to set an enrionment variable 'debug.tflite.trace' for profile
// scheme at Xcode to enable this profiler.
std::unique_ptr<tflite::Profiler> MaybeCreateSignpostProfiler();

}  // namespace profiling
}  // namespace tflite

#endif  // TENSORFLOW_LITE_PROFILING_SIGNPOST_PROFILER_H_
