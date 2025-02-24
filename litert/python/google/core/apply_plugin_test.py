# Copyright 2024 The TensorFlow Authors. All Rights Reserved.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# ==============================================================================


import pathlib
import subprocess
from unittest import mock

from google3.testing.pybase import googletest
from google3.third_party.odml.litert.litert.python.google.core import apply_plugin
from google3.third_party.odml.litert.litert.python.google.core import test_common


class ApplyPluginTest(test_common.TestWithTfliteModels):

  @property
  def output_name(self) -> str:
    return "output.tflite"

  @property
  def output_model(self) -> pathlib.Path:
    return self.output_dir() / self.output_name

  @property
  def input_model(self) -> pathlib.Path:
    return self.get_model_path("add_simple.tflite")

  @property
  def soc_manufacturer(self) -> str:
    return "ExampleSocManufacturer"

  @property
  def soc_model(self) -> str:
    return "ExampleSocModel"

  @mock.patch.object(subprocess, "run")
  def test_apply_plugin(self, mck: mock.Mock):
    mck.side_effect = self.get_touch_side_effect(self.output_model, 0)
    apply_plugin.ApplyPlugin()(
        self.input_model,
        self.output_model,
        self.soc_manufacturer,
        self.soc_model,
    )
    cmd_str = " ".join(mck.call_args_list[0][0][0])
    self.assertIn(str(self.input_model), cmd_str)
    self.assertIn(str(self.output_model), cmd_str)
    self.assertIn(self.soc_manufacturer, cmd_str)
    self.assertIn(self.soc_model, cmd_str)
    self.assertIn("apply_plugin_main", cmd_str)

  @mock.patch.object(subprocess, "run", return_value=0)
  def test_apply_plugin_no_file(self, unused_mock: mock.Mock):
    with self.assertRaises(ValueError):
      apply_plugin.ApplyPlugin()(
          self.input_model,
          self.output_model,
          self.soc_manufacturer,
          self.soc_model,
      )


if __name__ == "__main__":
  googletest.main()
