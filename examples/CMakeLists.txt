# CMake 3.8 is the minimum requirement because that is when CMAKE_CXX_STANDARD and 
# CMAKE_CXX_STANDARD_REQUIRED was introduced 
cmake_minimum_required(VERSION 3.8)

#set the standard to C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# the project function sets the name of the project
project(mtl-examples)

# macro to get all subdirectories in the current folder
macro(GETSUBDIR output_variable current_dir)
  file(GLOB children RELATIVE ${current_dir} ${current_dir}/*)
  set(dirlist "")
  foreach(child ${children})
    if(IS_DIRECTORY ${current_dir}/${child})
        # if the directory isn't the build directory
        if(NOT ${current_dir}/${child} MATCHES ${CMAKE_CURRENT_BINARY_DIR})
          # if the directory isn't a directory named mtl
          if(NOT "mtl" STREQUAL ${child})
            # add the directory to the list
            set(dirlist ${dirlist} ${child})
          endif()
        endif()
    endif()
  endforeach()
  set(${output_variable} ${dirlist})
endmacro()

# use the macro to set the subdirectories variable to a list of subdirectories
GETSUBDIR(subdirectories ${CMAKE_CURRENT_SOURCE_DIR})

# use foreach to loop over all subdirectories and add them
foreach(subdirectory ${subdirectories})
  # print a message that a subdirectory was added
  message("-- Added subdirectory ${subdirectory} as a subproject.")
  # add each subdirectory we want to compile with add_subdirectory
  add_subdirectory(${subdirectory}) 
endforeach()