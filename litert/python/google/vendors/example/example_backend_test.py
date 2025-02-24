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

from unittest import mock

from google3.testing.pybase import googletest
from google3.third_party.odml.litert.litert.python.google.core import components
from google3.third_party.odml.litert.litert.python.google.core import test_common
from google3.third_party.odml.litert.litert.python.google.core import types
from google3.third_party.odml.litert.litert.python.google.vendors.example import example_backend


class MockComponent:

  @property
  def component_name(self) -> str:
    return "mock_component"

  def __call__(self, *args, **kwargs):
    pass


class MockAieQuantizer(components.AieQuantizerT):

  @property
  def default_recipe(self) -> components.QuantRecipe:
    return []

  def __call__(self, *args, **kwargs):
    pass


class MockApplyPlugin(components.ApplyPluginT):

  def __call__(self, *args, **kwargs):
    pass


class MockMlirTransforms(components.MlirTransformsT):

  def __call__(self, *args, **kwargs):
    pass


class ExampleBackendTest(test_common.TestWithTfliteModels):

  @property
  def basic_config(self) -> types.Config:
    return {
        "backend_id": example_backend.ExampleBackend.id(),
        "output_dir": self.output_dir(),
    }

  @property
  def output_model(self) -> types.Model:
    return self.output_dir() / "output.tflite"

  def test_unsupported_component(self):
    backend = example_backend.ExampleBackend.create(self.basic_config)
    with self.assertRaisesRegex(
        NotImplementedError,
        "example backend does not support mock_component component.",
    ):
      model = types.Model("add_simple.tflite")
      component = MockComponent()
      backend.call_component(model, self.output_model, component)

  @mock.patch.object(MockApplyPlugin, "__call__")
  def test_apply_plugin(self, mck: mock.Mock):
    backend = example_backend.ExampleBackend.create(self.basic_config)
    model = types.Model("add_simple.tflite")
    component = MockApplyPlugin()
    backend.call_component(model, self.output_model, component)
    mck.assert_called_once()

  @mock.patch.object(MockAieQuantizer, "__call__")
  def test_aie_quantizer(self, mck: mock.Mock):
    backend = example_backend.ExampleBackend.create(self.basic_config)
    model = types.Model("add_simple.tflite")
    component = MockAieQuantizer()
    backend.call_component(model, self.output_model, component)
    mck.assert_called_once()

  @mock.patch.object(MockMlirTransforms, "__call__")
  def test_mlir_transforms(self, mck: mock.Mock):
    backend = example_backend.ExampleBackend.create(self.basic_config)
    model = types.Model("add_simple.tflite")
    component = MockMlirTransforms()
    backend.call_component(model, self.output_model, component)
    mck.assert_called_once()

  def test_bad_config(self):
    config = {}
    with self.assertRaisesRegex(ValueError, "Invalid backend id"):
      example_backend.ExampleBackend.create(config)


if __name__ == "__main__":
  googletest.main()
