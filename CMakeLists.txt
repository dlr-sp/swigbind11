# See the file "LICENSE" for the full license governing this code.
cmake_minimum_required(VERSION 3.18)
project(${SKBUILD_PROJECT_NAME} VERSION ${SKBUILD_PROJECT_VERSION} LANGUAGES CXX)

enable_language(CXX)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Generate swigpyrun.h while installing swigbind11
find_package(SWIG REQUIRED)
include(${SWIG_USE_FILE})

set(BINARY_INCLUDE_DIR "${CMAKE_CURRENT_BINARY_DIR}/include")
set(SWIGPYRUN_OUTPUT "${BINARY_INCLUDE_DIR}/swigpyrun.h")

file(MAKE_DIRECTORY ${BINARY_INCLUDE_DIR})

add_custom_command(
    OUTPUT ${SWIGPYRUN_OUTPUT}
    COMMAND ${SWIG_EXECUTABLE} -python -external-runtime ${SWIGPYRUN_OUTPUT}
    COMMENT "Generating swigpyrun.h"
    VERBATIM
)

add_custom_target(generate_swigpyrun ALL DEPENDS ${SWIGPYRUN_OUTPUT})

# # Use relative paths for DESTINATION to ensure the package is relocatable.
set(swigbind11_REL_ROOT "swigbind11")

# --- Library Targets ---
add_library(swigbind11 INTERFACE)
add_library(swigbind11::swigbind11 ALIAS swigbind11)
add_library(swigbind11::headers ALIAS swigbind11)

target_include_directories(
  swigbind11 INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
    $<INSTALL_INTERFACE:${swigbind11_REL_ROOT}/include>
)

target_compile_features(swigbind11 INTERFACE cxx_std_17)

set(swigbind11_INCLUDE_DIR "\$\{PACKAGE_PREFIX_DIR\}/swigbind11/include")
set(swigbind11_REL_CMAKE_DEST "${swigbind11_REL_ROOT}/share/cmake")

# --- Configuration Files ---
configure_package_config_file(
    "tools/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    INSTALL_DESTINATION "${swigbind11_REL_CMAKE_DEST}"
)

# --- Installation Logic ---

# 1. Install Python source files (the __init__.py and other scripts)
install(DIRECTORY "swigbind11/"
        DESTINATION "${swigbind11_REL_ROOT}")

# 2. Install C++ Headers into swigbind11/include/
install(DIRECTORY "include/swigbind11"
        DESTINATION "${swigbind11_REL_ROOT}/include")

install(FILES ${SWIGPYRUN_OUTPUT} DESTINATION "${swigbind11_REL_ROOT}/include/swigbind11")

# 3. Install CMake Config into swigbind11/share/cmake/
install(TARGETS swigbind11 EXPORT swigbind11Targets)

install(EXPORT swigbind11Targets
    FILE swigbind11Targets.cmake
    NAMESPACE swigbind11::
    DESTINATION "${swigbind11_REL_CMAKE_DEST}"
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        DESTINATION "${swigbind11_REL_CMAKE_DEST}")
