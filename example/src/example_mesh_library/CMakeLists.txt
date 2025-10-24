
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
find_package(SWIG REQUIRED)

include(UseSWIG)

set(CMAKE_SWIG_FLAGS "-c++")
set_property(SOURCE mesh.i PROPERTY CPLUSPLUS on)

add_library(mesh_core SHARED mesh.cpp)
target_include_directories(mesh_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

swig_add_library(swig_mesh_bindings
    TYPE MODULE
    LANGUAGE python
    SOURCES mesh.i
)

target_link_libraries(swig_mesh_bindings
    PRIVATE
        mesh_core
        Python3::Python
)

target_include_directories(swig_mesh_bindings PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# add the installation location of the bindings to their RPATH, such that the C extension directly finds the library
set_target_properties(swig_mesh_bindings PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "$ORIGIN"
)

include(GNUInstallDirs)

set(SWIG_PACKAGE_DIR ${Python3_SITEARCH}/example_mesh_library)

install(TARGETS swig_mesh_bindings mesh_core
    LIBRARY DESTINATION ${SWIG_PACKAGE_DIR}
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/mesh.py
    DESTINATION ${SWIG_PACKAGE_DIR}
)

install(CODE "file(WRITE ${SWIG_PACKAGE_DIR}/__init__.py \"# example_mesh_library package init \n
from .mesh import Mesh \n\")"
)
