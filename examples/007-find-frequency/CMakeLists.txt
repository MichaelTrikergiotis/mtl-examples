# CMake script by Michael Trikergiotis

# Copyright (c) Michael Trikergiotis. All Rights Reserved.
# Licensed under the MIT license. See LICENSE in the project root for license information.
# See ThirdPartyNotices.txt in the project root for third party licenses information.

# CMake 3.8 is the minimum requirement because that is when CMAKE_CXX_STANDARD and 
# CMAKE_CXX_STANDARD_REQUIRED was introduced 
cmake_minimum_required(VERSION 3.8)

# if the C++ standard version isn't defined, set it to C++ 17, if it is defined use that version
if(NOT DEFINED CMAKE_CXX_STANDARD)
    # set standard version to C++ 17
    set(CMAKE_CXX_STANDARD 17)
endif()

# require the C++ standard version to be provided
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# if the C++ standard version is not set to C++ 17 or later, print a message and invoke a
# fatal error
if(NOT (${CMAKE_CXX_STANDARD} GREATER_EQUAL 17))
    message(FATAL_ERROR "The mtl requires the C++ standard version to be C++ 17 or later.")
endif()

# get the name of the current folder to use as the project name
get_filename_component(EXAMPLENAME ${CMAKE_CURRENT_LIST_DIR} NAME)
# replace all spaces
string(REPLACE " " "-" EXAMPLENAME ${EXAMPLENAME})

# set the name of the project
project(${EXAMPLENAME})

# add_executable function adds the sources files to the project letting CMake know what to compile
add_executable(${EXAMPLENAME} example.cpp)
