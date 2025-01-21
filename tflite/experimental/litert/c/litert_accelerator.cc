// Copyright 2025 Google LLC.
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

#include "tflite/experimental/litert/c/litert_accelerator.h"

#include "tflite/experimental/litert/c/litert_common.h"
#include "tflite/experimental/litert/cc/litert_expected.h"
#include "tflite/experimental/litert/core/accelerator.h"
#include "tflite/experimental/litert/core/environment.h"

// Gets the number of accelerators registered to LiteRT.
LiteRtStatus LiteRtGetNumAccelerators(LiteRtParamIndex* num_accelerators) {
  if (!num_accelerators) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  litert::Expected<litert::internal::Environment*> environment =
      litert::internal::Environment::Instance();
  if (!environment.HasValue()) {
    return environment.Error().Status();
  }
  *num_accelerators = environment.Value()->GetAcceleratorRegistry().size();
  return kLiteRtStatusOk;
}

// Gets the accelerator at given index that is registered to LiteRT.
LiteRtStatus LiteRtGetAccelerator(LiteRtParamIndex index,
                                  LiteRtAccelerator* accelerator) {
  if (!accelerator) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  litert::Expected<litert::internal::Environment*> environment =
      litert::internal::Environment::Instance();
  if (!environment.HasValue()) {
    return environment.Error().Status();
  }
  litert::Expected<LiteRtAccelerator> registered_accelerator =
      environment.Value()->GetAcceleratorRegistry().Get(index);
  if (!registered_accelerator.HasValue()) {
    return registered_accelerator.Error().Status();
  }
  *accelerator = registered_accelerator.Value();
  return kLiteRtStatusOk;
}

LiteRtStatus LiteRtGetAcceleratorName(LiteRtAccelerator accelerator,
                                      char const** name) {
  if (!accelerator) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  if (!accelerator->GetName) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  if (!name) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  return accelerator->GetName(accelerator, name);
}

LiteRtStatus LiteRtGetAcceleratorId(LiteRtAccelerator accelerator,
                                    LiteRtAcceleratorId* id) {
  if (!accelerator) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  if (!id) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  litert::Expected<litert::internal::Environment*> environment =
      litert::internal::Environment::Instance();
  if (!environment.HasValue()) {
    return environment.Error().Status();
  }
  litert::Expected<LiteRtParamIndex> index =
      environment.Value()->GetAcceleratorRegistry().FindAcceleratorIndex(
          accelerator);
  if (!index.HasValue()) {
    return index.Error().Status();
  }
  *id = index.Value();
  return kLiteRtStatusOk;
}

LiteRtStatus LiteRtGetAcceleratorVersion(LiteRtAccelerator accelerator,
                                         LiteRtApiVersion* version) {
  if (!accelerator) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  if (!accelerator->GetVersion) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  if (!version) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  return accelerator->GetVersion(accelerator, version);
}

LiteRtStatus LiteRtGetAcceleratorHardwareSupport(
    LiteRtAccelerator accelerator, LiteRtHwAcceleratorSet* supported_hardware) {
  if (!accelerator) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  if (!accelerator->GetHardwareSupport) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  if (!supported_hardware) {
    return kLiteRtStatusErrorInvalidArgument;
  }
  return accelerator->GetHardwareSupport(accelerator, supported_hardware);
}
