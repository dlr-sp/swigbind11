# See the file "LICENSE" for the full license governing this code.
cmake_minimum_required(VERSION 3.18)
project(swigbind11)

enable_language(CXX)

include(GNUInstallDirs)

set(Python_FIND_STRATEGY LOCATION)

find_package(Python3 COMPONENTS Interpreter Development.Module REQUIRED)

# If we are in a venv and no prefix was manually set...
if(DEFINED ENV{VIRTUAL_ENV} AND CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    # Force the install prefix to the virtual environment root
    set(CMAKE_INSTALL_PREFIX "$ENV{VIRTUAL_ENV}" CACHE PATH "..." FORCE)
endif()

set(swigbind11_INCLUDE_DIR
    "${CMAKE_CURRENT_LIST_DIR}/include"
    CACHE INTERNAL "Directory where swigbind11 header is located")

set(swigbind11_INSTALL_DIR "${Python3_SITEARCH}/swigbind11")

set(CMAKE_INSTALL_DATAROOTDIR "${swigbind11_INSTALL_DIR}/share")

set(swigbind11_CMAKECONFIG_INSTALL_DIR
    "${CMAKE_INSTALL_DATAROOTDIR}/cmake/${PROJECT_NAME}"
    CACHE STRING "install path for pybind11Config.cmake")

add_library(swigbind11 INTERFACE)
add_library(swigbind11::swigbind11 ALIAS swigbind11)
add_library(swigbind11::headers ALIAS swigbind11)

target_include_directories(
  swigbind11 INTERFACE $<BUILD_INTERFACE:${swigbind11_INCLUDE_DIR}>
                       $<INSTALL_INTERFACE:include>)

target_compile_features(swigbind11 INTERFACE cxx_std_17)

configure_file(
    "tools/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    @ONLY
)

install(DIRECTORY ${swigbind11_INCLUDE_DIR}/swigbind11 DESTINATION ${CMAKE_INSTALL_PREFIX}/include)

install(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/swigbind11 DESTINATION ${Python3_SITEARCH})

install(TARGETS swigbind11 EXPORT swigbind11Targets)

install(EXPORT swigbind11Targets
    FILE swigbind11Targets.cmake
    NAMESPACE swigbind11::
    DESTINATION ${swigbind11_CMAKECONFIG_INSTALL_DIR}
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake DESTINATION ${swigbind11_CMAKECONFIG_INSTALL_DIR})

