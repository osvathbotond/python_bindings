import unittest
from pkgutil import walk_packages
from importlib import import_module
import build
import tests

for _, name, _ in walk_packages(build.__path__, f"{build.__name__}."):
    if name.endswith(".quaternion"):
        quaternion = import_module(name)
        tests.QuaternionTest.setQuaternion(quaternion.Quaternion, name)
        unittest.main(tests.QuaternionTest(), exit=False)