# See the file "LICENSE" for the full license governing this code.
cmake_minimum_required(VERSION 3.18)
project(swigbind11)

enable_language(CXX)

add_library(swigbind11 INTERFACE)
add_library(swigbind11::swigbind11 ALIAS swigbind11)
add_library(swigbind11::headers ALIAS swigbind11)

include(GNUInstallDirs)

target_include_directories(
  swigbind11 INTERFACE $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
                       $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

target_compile_features(swigbind11 INTERFACE cxx_std_17)

install(TARGETS swigbind11)
