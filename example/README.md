# Example for *swigbind11*

This is the minimum working example of creating a *pybind11* wrapped plugin that interfaces with another *swig* wrapped C++ library.

The *example_mesh_library* is a C++ library wrapped to Python using *SWIG*, while for the plugin *meshplugin* we want to use *pybind11*. This sample code demonstrates how to pass the type `Mesh`, defined in *example_mesh_library*, between Python and the C++ side of the plugin using *swigbind11*, while automatically performing the necessary type conversions.

## Defining holder types and custom type casters

By default, *pybind11* uses `std::unique_ptr<T>` as a *holder type* for a given
C++ type `T`. The lifetime of objects created on the Python side or the C++ side
which are referenced also on the respective other side of the interface has to
be tracked carefully to avoid dangling references or issues with the Python GC.
To simplify this task for common use cases, *swigbind11* uses
`std::shared_ptr<T>` with a custom deleter as a holder type, which should support
proper lifetime tracking.

In order for `pybind11` to map C++ types to the existing (but externally
defined) SWIG Python types and vice versa, it is necessary to set up
[custom type casters](https://pybind11.readthedocs.io/en/stable/advanced/cast/custom.html).
Instead of using the low-level functionality of *swigbind11* (i.e.,
`swig_py_cast` and `py_swig_cast`), the macro
`SWIGBIND11_TYPE_CASTER(cpp_type, python_type)` defined by *swigbind11* can be
used to set up the type casting between the C++ type `cpp_type` and the Python
type `python_type` taking into account the correct holder type,
`std::shared_ptr<cpp_type>`.

- `SWIGBIND11_TYPE_CASTER(cpp_type, python_type)`

## Dependencies

- C++ compiler supporting C++17 (tested with GNU 11.4.0)
- CMake >= 3.18
- Python >= 3.7
- SWIG >= 4.0
- pytest
- swigbind11 **conditional**

``swigbind11`` **Version Mapping**

Due to breaking changes in SWIG's internal logic, please ensure you use the version of ``swigbind11`` that matches your installed SWIG version:

- SWIG < 4.4.0: Use swigbind11 v1.1.0
- SWIG ≥ 4.4.0: Use swigbind11 v1.2.0

## Installation

Make sure you are in folder swigbind11/example.

Create and activate a virtual environment
```shell
python3 -m venv venv
source venv/bin/activate
```

After you obtained the source code, the project can be configured and build
in the default configuration via:
```shell
pip install .
```

## Testing

Tests can be run via:
```shell
pytest
```
