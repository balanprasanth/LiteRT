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

#include "third_party/odml/litert/litert/core/environment.h"

#include <any>
#include <array>

#include "testing/base/public/gunit.h"
#include "third_party/odml/litert/litert/c/litert_any.h"
#include "third_party/odml/litert/litert/c/litert_environment.h"
#include "third_party/odml/litert/litert/cc/litert_any.h"

namespace litert::internal {
namespace {

TEST(LiteRtEnvironmentT, CreateWithOptions) {
  const std::array<LiteRtEnvOption, 1> environment_options = {
      LiteRtEnvOption{
          kLiteRtEnvOptionTagCompilerPluginLibraryDir,
          *ToLiteRtAny(std::any("sample path")),
      },
  };
  auto env = LiteRtEnvironmentT::CreateWithOptions(environment_options);
  ASSERT_TRUE(env);

  auto option = (*env)->GetOption(kLiteRtEnvOptionTagCompilerPluginLibraryDir);
  ASSERT_TRUE(option.has_value());
  ASSERT_EQ(option->type, kLiteRtAnyTypeString);
  ASSERT_STREQ(option->str_value, "sample path");
}

}  // namespace
}  // namespace litert::internal
