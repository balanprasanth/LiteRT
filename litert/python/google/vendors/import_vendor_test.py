# Copyright 2025 The TensorFlow Authors. All Rights Reserved.
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

from google3.testing.pybase import googletest
from google3.third_party.odml.litert.litert.python.google.core import types
from google3.third_party.odml.litert.litert.python.google.vendors import import_vendor


class ImportVendorTest(googletest.TestCase):

  def test_import_example_backend(self):
    backend = import_vendor.import_vendor("example")
    self.assertIsInstance(backend, types.Backend.__class__)
    self.assertEqual(backend.id(), "example")

  def test_import_backend_not_found(self):
    with self.assertRaises(ValueError):
      import_vendor.import_vendor("non_existent_backend")


if __name__ == "__main__":
  googletest.main()
