#! /bin/sh

mkdir -p build/cpp/pybind11
mkdir -p build/cpp/boost
mkdir -p build/c/capi

touch build/__init__.py
touch build/cpp/__init__.py
touch build/cpp/pybind11/__init__.py
touch build/cpp/boost/__init__.py
touch build/c/__init__.py
touch build/c/capi/__init__.py

g++ -O3 -std=c++20 -fPIC -shared $(python3 -m pybind11 --includes) ./cpp/pybind11.cpp -o ./build/cpp/pybind11/quaternion$(python3-config --extension-suffix)
g++ -O3 -std=c++20 -fPIC -shared ./cpp/boost.cpp $(python3-config --includes) -lboost_python310 -o ./build/cpp/boost/quaternion$(python3-config --extension-suffix)
gcc -O3 -std=c11 -fPIC -shared ./c/capi.c $(python3-config --includes) -o ./build/c/capi/quaternion$(python3-config --extension-suffix)
