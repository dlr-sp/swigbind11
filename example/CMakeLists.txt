# example project illustrating the usage of swigbind11 by interfacing FSDM
# (SWIG-wrapped) with a demo plugin
cmake_minimum_required(VERSION 3.18)
project(fsplugin)

enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

# for a real plugin, you would probably add 'swigbind11' as a Git submodule at
# the appropriate location, e.g., '${PROJECT_SOURCE_DIR}/third_party/swigbind11'
set(SWIGBIND11_ROOT "../")

# same goes for pybind11
set(PYBIND11_ROOT "../third_party/pybind11")

# prefer first detected Python version to avoid issues with virtual environments
set(Python_FIND_STRATEGY LOCATION)

set(python_components Interpreter Development.Module)

find_package(
  Python 3.7
  COMPONENTS ${python_components}
  REQUIRED)

# FSDM as external dependency
find_package(PkgConfig REQUIRED)
pkg_check_modules(FSDM REQUIRED IMPORTED_TARGET fsdm)
message(STATUS "FSDM v" ${FSDM_VERSION})

# pybind11 shipped as a third-party dependency
add_subdirectory(${PYBIND11_ROOT} "third_party/pybind11" EXCLUDE_FROM_ALL)

# swigbind11 shipped as a third-party dependency
add_subdirectory(${SWIGBIND11_ROOT} "third_party/swigbind11" EXCLUDE_FROM_ALL)

pybind11_add_module(fsplugin MODULE fsplugin.cpp)

target_link_libraries(fsplugin PRIVATE PkgConfig::FSDM swigbind11::headers)

# enable generation of Clang compilation database for IDE integration
set(CMAKE_EXPORT_COMPILE_COMMANDS on)
