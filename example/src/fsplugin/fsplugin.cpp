// See the file "LICENSE" for the full license governing this code.

#include <memory>
#include <stdexcept>

#include <FSArray.h>
#include <FSClac.h>
#include <FSError.h>
#include <FSMesh.h>
#include <FSMeshData.h>
#include <FSQuantityDesc.h>
#include <FSUnstructMeshData.h>

#include <pybind11/pybind11.h>
#include <swigbind11/swigbind11.hpp>

namespace py = pybind11;

SWIGBIND11_TYPE_CASTER(FSClac, "FSDataManager.FSClac");  // NOLINT
SWIGBIND11_TYPE_CASTER(FSMesh, "FSDataManager.FSMesh");  // NOLINT

// NOLINTNEXTLINE
SWIGBIND11_TYPE_CASTER_TWO_SIDED(FSArrayPrimitiveT<FS_floatT>, "FSDataManager.FSArrayPrimitiveT<FS_floatT>",
                                 "FSDataManager.FSFloatArray");

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

  // NOLINTNEXTLINE(performance-unnecessary-value-param)
  void set_coordinates(const std::shared_ptr<FSArrayPrimitiveT<FS_floatT>> data) {
    if (!_mesh->IsUnstructured()) {
      throw std::runtime_error{"extraction of coordinates requires unstructured mesh"};
    }

    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    auto& mesh_data = const_cast<FSUnstructMeshData&>(_mesh->GetMeshData()->GetUnstructCells());

    auto coordinateDescriptions = FSQuantityDescArrayT{};
    if (!mesh_data.DetermineCoordinates(coordinateDescriptions)) {
      throw std::runtime_error{fmt::format("failed to determine coordinate description: {}", FSError.Get())};
    }

    if (!mesh_data.SetCoordinates3D(coordinateDescriptions, *data)) {
      throw std::runtime_error{fmt::format("failed to set node coordinates of mesh: {}", FSError.Get())};
    }
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
      .def("get_coordinates", &Foo::get_coordinates)
      .def("set_coordinates", &Foo::set_coordinates, py::arg("coordinates"));

  m.def("create_mesh", &create_mesh, py::arg("clac"));
}

}  // namespace fsplugin
