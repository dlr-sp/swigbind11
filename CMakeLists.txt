# See the file "LICENSE" for the full license governing this code.
cmake_minimum_required(VERSION 3.18)
project(swigbind11)

enable_language(CXX)

string(TOUPPER ${CMAKE_PROJECT_NAME}_WITH_ option_prefix)

# configuration options
option(${option_prefix}EXAMPLE "Build with example" on)

# set default build type
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE RelWithDebInfo)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

# optional: example
if(${option_prefix}EXAMPLE)
  message(STATUS "Enabling building of example")
  enable_testing()
  add_subdirectory(example)
endif()

add_library(swigbind11_headers INTERFACE)
add_library(swigbind11::headers ALIAS swigbind11_headers)

target_include_directories(swigbind11_headers INTERFACE ${PROJECT_SOURCE_DIR}/include)
