# CMake 3.8 is the minimum requirement because that is when CMAKE_CXX_STANDARD and 
# CMAKE_CXX_STANDARD_REQUIRED was introduced 
cmake_minimum_required(VERSION 3.8)

# set the standard to C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# get the name of the current folder to use as the project name
get_filename_component(EXAMPLENAME ${CMAKE_CURRENT_LIST_DIR} NAME)
# replace all spaces
string(REPLACE " " "-" EXAMPLENAME ${EXAMPLENAME})

# the project function sets the name of the project
project(${EXAMPLENAME})

# add_executable function adds the sources files to the project letting CMake know what to compile
add_executable(${EXAMPLENAME} example.cpp)
