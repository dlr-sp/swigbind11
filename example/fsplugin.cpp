// See the file "LICENSE" for the full license governing this code.

#include <iostream>
#include <stdexcept>
#include <string_view>

#include "pybind11/pybind11.h"

#include "swigbind11/swigbind11.hpp"

#include "FSMesh.h"


namespace py = pybind11;

using namespace py::literals;

namespace fsplugin {

class Plugin {
 public:
  explicit Plugin(FSMesh& mesh) : _mesh{mesh} {}

  void process() {
    // fancy operation on the FSMesh
    std::cout << "Processing FSMesh...." << std::endl;
    _mesh.PrintInfo();
  }

 private:
  FSMesh& _mesh;
};

PYBIND11_MODULE(fsplugin, m) {
  py::class_<Plugin, std::shared_ptr<Plugin>>(m, "Plugin")
      .def(py::init<>([](py::object swig_fsmesh_proxy) {
        auto mesh = swigbind11::swig_py_cast<FSMesh>(swig_fsmesh_proxy, "FSDataManager.FSMesh");

        return Plugin{*mesh};
      }))
      .def("process", &Plugin::process);
}

}  // namespace fsplugin
