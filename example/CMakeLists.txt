# prefer first detected Python version to avoid issues with virtual environments
set(Python_FIND_STRATEGY LOCATION)

set(python_components Interpreter Development.Module)

find_package(
  Python 3.7
  COMPONENTS ${python_components}
  REQUIRED)

# dependency: FSDM
find_package(PkgConfig REQUIRED)
pkg_check_modules(FSDM REQUIRED IMPORTED_TARGET fsdm)
message(STATUS "FSDM v" ${FSDM_VERSION})

# pybind11 shipped as a third-party dependency
add_subdirectory("${PROJECT_SOURCE_DIR}/third_party/pybind11"
                 "third_party/pybind11" EXCLUDE_FROM_ALL)

pybind11_add_module(fsplugin MODULE fsplugin.cpp)

target_link_libraries(fsplugin PRIVATE PkgConfig::FSDM)

target_include_directories(fsplugin PUBLIC ${PROJECT_SOURCE_DIR}/include)

# enable generation of Clang compilation database for IDE integration
set(CMAKE_EXPORT_COMPILE_COMMANDS on)