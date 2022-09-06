// See the file "LICENSE" for the full license governing this code.

#include <iostream>
#include <memory>
#include <stdexcept>

#include "pybind11/pybind11.h"
#include "swigbind11/swigbind11.hpp"

#include "FSArray.h"
#include "FSClac.h"
#include "FSMesh.h"
#include "FSMeshData.h"
#include "FSUnstructMeshData.h"

namespace py = pybind11;

SWIGBIND11_TYPE_CASTER(FSClac, "FSDataManager.FSClac");                                              // NOLINT
SWIGBIND11_TYPE_CASTER(FSArrayPrimitiveT<FS_floatT>, "FSDataManager.FSArrayPrimitiveT<FS_floatT>");  // NOLINT
SWIGBIND11_TYPE_CASTER(FSMesh, "FSDataManager.FSMesh");                                              // NOLINT

namespace fsplugin {

class Foo {
 public:
  Foo() = default;

  explicit Foo(std::shared_ptr<FSMesh> mesh) : _mesh{std::move(mesh)} { _mesh->PrintInfo(); }

  [[nodiscard]] auto clone() const -> std::shared_ptr<FSMesh> { return std::make_shared<FSMesh>(*_mesh); }

  void info() const { _mesh->PrintInfo(); }

  [[nodiscard]] auto get_coordinates() const -> std::shared_ptr<FSArrayPrimitiveT<FS_floatT>> {
    if (!_mesh->IsUnstructured()) {
      throw std::runtime_error{"extraction of coordinates requires unstructured mesh"};
    }

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    auto& mesh_data = const_cast<FSUnstructMeshData&>(_mesh->GetMeshData()->GetUnstructCells());

    auto data = std::make_shared<FSArrayPrimitiveT<FS_floatT>>();
    auto coordinateDescriptions = FSQuantityDescArrayT{};
    auto nodeOffset = FS_intT{};

    mesh_data.GetCoordinates3D(coordinateDescriptions, *data, nodeOffset, /* enforceCopy = */ true);

    return data;
  }

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
      .def("info", &Foo::info)
      .def("get_coordinates", &Foo::get_coordinates);

  m.def("create_mesh", &create_mesh, py::arg("clac"));
}

}  // namespace fsplugin
