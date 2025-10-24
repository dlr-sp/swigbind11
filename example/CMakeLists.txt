# example project illustrating the usage of swigbind11 by interfacing
# Mesh (SWIG-wrapped) with a demo plugin meshplugin
cmake_minimum_required(VERSION 3.18)
project(meshplugin)

enable_language(CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_EXTENSIONS off)

# enable generation of Clang compilation database for IDE integration
set(CMAKE_EXPORT_COMPILE_COMMANDS on)

# prefer first detected Python version to avoid issues with virtual environments
set(Python_FIND_STRATEGY LOCATION)

find_package(Python3 COMPONENTS Interpreter Development.Module REQUIRED)

# for a real plugin, you would probably add 'swigbind11' as a Git submodule at
# the appropriate location, e.g., '${PROJECT_SOURCE_DIR}/third_party/swigbind11'
set(SWIGBIND11_ROOT "${PROJECT_SOURCE_DIR}/../")

# for pybind11, either the version included in swigbind11 can be used or a
# project-specific one, e.g., '${PROJECT_SOURCE_DIR}/third_party/pybind11'
set(PYBIND11_ROOT "${PROJECT_SOURCE_DIR}/third_party/pybind11")

# pybind11 shipped as a third-party dependency
add_subdirectory(${PYBIND11_ROOT} "third_party/pybind11" EXCLUDE_FROM_ALL)

# # swigbind11 shipped as a third-party dependency
add_subdirectory(${SWIGBIND11_ROOT} "third_party/swigbind11" EXCLUDE_FROM_ALL)

# subdirectories for the swig-wrapped mesh and pybind11-wrapped mesh plugin
add_subdirectory(src/example_mesh_library)
add_subdirectory(src/meshplugin)
