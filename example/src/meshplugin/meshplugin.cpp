// See the file "LICENSE" for the full license governing this code.

#include <memory>
#include <stdexcept>
#include <iostream>

#include "mesh.hpp"
#include <pybind11/pybind11.h>

#include <swigbind11/swigbind11.hpp>

namespace py = pybind11;

SWIGBIND11_TYPE_CASTER(Mesh, "example_mesh_library.mesh.Mesh");  // NOLINT

namespace meshplugin {

class Foo {
 public:
  Foo() = default;

  explicit Foo(std::shared_ptr<Mesh> mesh) : _mesh{std::move(mesh)} { }

  [[nodiscard]] std::shared_ptr<Mesh> clone() const { return std::make_shared<Mesh>(*_mesh); }

  void info() const { _mesh->printInfo(); }

 private:
  std::shared_ptr<Mesh> _mesh;
};

std::shared_ptr<Mesh> create_mesh() {
  return std::make_shared<Mesh>();
}

PYBIND11_MODULE(_meshplugin, m) {  // NOLINT
  py::class_<Foo>(m, "Foo")
      .def(py::init<>())
      .def(py::init<std::shared_ptr<Mesh>>(), py::arg("mesh"))
      .def("clone", &Foo::clone)
      .def("info", &Foo::info);

  m.def("create_mesh", &create_mesh);
}

}  // namespace meshplugin
