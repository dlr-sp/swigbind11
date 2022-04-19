// See the file "LICENSE" for the full license governing this code.

#include <iostream>
#include <memory>

#include "pybind11/pybind11.h"
#include "swigbind11/swigbind11.hpp"

#include "FSClac.h"
#include "FSMesh.h"

namespace py = pybind11;

SWIGBIND11_TYPE_CASTER(FSMesh, "FSDataManager.FSMesh");  // NOLINT
SWIGBIND11_TYPE_CASTER(FSClac, "FSDataManager.FSClac");  // NOLINT

namespace fsplugin {

class Foo {
 public:
  Foo() = default;

  explicit Foo(std::shared_ptr<FSMesh> mesh) : _mesh{std::move(mesh)} { _mesh->PrintInfo(); }

  [[nodiscard]] auto clone() const -> std::shared_ptr<FSMesh> { return std::make_shared<FSMesh>(*_mesh); }

  void info() const { _mesh->PrintInfo(); }

 private:
  std::shared_ptr<FSMesh> _mesh = nullptr;
};

auto create_mesh(const std::shared_ptr<FSClac>& clac) -> std::shared_ptr<FSMesh> {
  return std::make_shared<FSMesh>(clac.get());
}

PYBIND11_MODULE(_fsplugin, m) {  // NOLINT
  py::class_<Foo>(m, "Foo")
      .def(py::init<>())
      .def(py::init<std::shared_ptr<FSMesh>>(), py::arg("mesh"))
      .def("clone", &Foo::clone)
      .def("info", &Foo::info);

  m.def("create_mesh", &create_mesh, py::arg("clac"));
}

}  // namespace fsplugin
