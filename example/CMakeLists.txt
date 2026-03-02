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

execute_process(
    COMMAND ${Python3_EXECUTABLE} -m pybind11 --cmakedir
    OUTPUT_VARIABLE pybind11_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

find_package(pybind11 REQUIRED)

execute_process(
    COMMAND ${Python3_EXECUTABLE} -m swigbind11 --cmakedir
    OUTPUT_VARIABLE swigbind11_DIR
    OUTPUT_STRIP_TRAILING_WHITESPACE
)

find_package(swigbind11 REQUIRED)

# subdirectories for the swig-wrapped mesh and pybind11-wrapped mesh plugin
add_subdirectory(src/example_mesh_library)
add_subdirectory(src/meshplugin)
