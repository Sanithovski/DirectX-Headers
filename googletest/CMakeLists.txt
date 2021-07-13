# Copyright (c) Microsoft Corporation.
# Licensed under the MIT License.
add_subdirectory(googletest)

project(DirectX-Headers-GoogleTest-Suite CXX)
add_executable(Feature-Support-Test feature_support_test.cpp)
target_link_libraries(Feature-Support-Test DirectX-Headers DirectX-Guids d3d12 dxcore gtest_main)
