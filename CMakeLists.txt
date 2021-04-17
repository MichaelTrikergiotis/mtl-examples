# CMake script by Michael Trikergiotis

# Copyright (c) Michael Trikergiotis. All Rights Reserved.
# Licensed under the MIT license. See LICENSE in the project root for license information.
# See ThirdPartyNotices.txt in the project root for third party licenses information.

# CMake 3.8 is the minimum requirement because that is when CMAKE_CXX_STANDARD and 
# CMAKE_CXX_STANDARD_REQUIRED was introduced 
cmake_minimum_required(VERSION 3.8)

#set the standard to C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# the project function sets the name of the project
project(mtl-examples)

# add the subdirectory containing all the examples
add_subdirectory(examples)