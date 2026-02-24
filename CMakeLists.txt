# See the file "LICENSE" for the full license governing this code.
cmake_minimum_required(VERSION 3.18)
project(swigbind11)

enable_language(CXX)
include(GNUInstallDirs)

# # --- Python Discovery ---
# find_package(Python3 COMPONENTS Interpreter Development.Module REQUIRED)

# # --- Define Internal Package Paths ---
# set(swigbind11_PY_PACKAGE_DIR "swigbind11")

# # Use relative paths for DESTINATION to ensure the package is relocatable.
set(swigbind11_REL_ROOT "swigbind11")

# --- Library Targets ---
add_library(swigbind11 INTERFACE)
add_library(swigbind11::swigbind11 ALIAS swigbind11)
add_library(swigbind11::headers ALIAS swigbind11)

target_include_directories(
  swigbind11 INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${swigbind11_REL_ROOT}/include>
)

target_compile_features(swigbind11 INTERFACE cxx_std_17)

# --- Configuration Files ---
configure_file(
    "tools/${PROJECT_NAME}Config.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
    @ONLY
)

# --- Installation Logic ---

# 1. Install Python source files (the __init__.py and other scripts)
install(DIRECTORY "swigbind11/"
        DESTINATION "${swigbind11_REL_ROOT}")

# 2. Install C++ Headers into swigbind11/include/
install(DIRECTORY "include/swigbind11"
        DESTINATION "${swigbind11_REL_ROOT}/include")

# 3. Install CMake Config into swigbind11/share/cmake/
set(swigbind11_REL_CMAKE_DEST "${swigbind11_REL_ROOT}/share/cmake")

install(TARGETS swigbind11 EXPORT swigbind11Targets)

install(EXPORT swigbind11Targets
    FILE swigbind11Targets.cmake
    NAMESPACE swigbind11::
    DESTINATION "${swigbind11_REL_CMAKE_DEST}"
)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Config.cmake"
        DESTINATION "${swigbind11_REL_CMAKE_DEST}")
