pybind11_add_module(_meshplugin MODULE meshplugin.cpp)

add_dependencies(_meshplugin mesh_core)

target_link_libraries(
  _meshplugin
  PRIVATE
    mesh_core
    pybind11::headers
    swigbind11::headers
)
target_include_directories(_meshplugin PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/../example_mesh_library)

set(PY_PACKAGE_DIR "${Python3_SITEARCH}/meshplugin")

# add the installation location of the C++ library to the RPATH to ensure that our C extension finds it automatically
set_target_properties(_meshplugin PROPERTIES
    BUILD_WITH_INSTALL_RPATH TRUE
    INSTALL_RPATH "${Python3_SITEARCH}/example_mesh_library"
)

include(GNUInstallDirs)

install(TARGETS _meshplugin
    LIBRARY DESTINATION ${PY_PACKAGE_DIR}
)

install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/__init__.py"
        DESTINATION ${PY_PACKAGE_DIR}
)
