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

#ifndef TENSORFLOW_LITE_EXPERIMENTAL_LITERT_RUNTIME_EVENT_H_
#define TENSORFLOW_LITE_EXPERIMENTAL_LITERT_RUNTIME_EVENT_H_

#include <cstdint>

#include "tflite/experimental/litert/c/litert_common.h"
#include "tflite/experimental/litert/cc/litert_expected.h"

struct LiteRtEventT {
#if LITERT_HAS_SYNC_FENCE_SUPPORT
  int fd = -1;
  bool owns_fd = false;
#endif
  ~LiteRtEventT();
  litert::Expected<void> Wait(int64_t timeout_in_ms);
  litert::Expected<int> GetSyncFenceFd() const {
#if LITERT_HAS_SYNC_FENCE_SUPPORT
    return fd;
#else
    return litert::Unexpected(kLiteRtStatusErrorRuntimeFailure,
                              "Sync fence is not supported on this platform");
#endif
  }
};

#endif  // TENSORFLOW_LITE_EXPERIMENTAL_LITERT_RUNTIME_EVENT_H_
