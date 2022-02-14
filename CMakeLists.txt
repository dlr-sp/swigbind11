# See the file "LICENSE" for the full license governing this code.
cmake_minimum_required(VERSION 3.18)
project(swigbind11)

enable_language(CXX)

add_library(swigbind11_headers INTERFACE)
add_library(swigbind11::headers ALIAS swigbind11_headers)

target_include_directories(swigbind11_headers
                           INTERFACE ${PROJECT_SOURCE_DIR}/include)
