set(python_module_name _fsplugin)

pybind11_add_module(${python_module_name} MODULE fsplugin.cpp)

target_link_libraries(
  ${python_module_name} PRIVATE PkgConfig::FSDM pybind11::headers
                                swigbind11::headers)

file(COPY "__init__.py" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

install(TARGETS ${python_module_name} DESTINATION .)

include(GNUInstallDirs)

set(python_install_dir
    "${CMAKE_INSTALL_LIBDIR}/python${Python_VERSION_MAJOR}.${Python_VERSION_MINOR}/site-packages/${package_name}"
)

install(TARGETS ${python_module_name} LIBRARY DESTINATION ${python_install_dir}
                                              COMPONENT python)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/__init__.py"
        DESTINATION ${python_install_dir})
