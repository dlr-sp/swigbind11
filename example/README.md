# Example for *swigbind11*: FSPlugin using *pybind11*

This is the minimum working example of creating a *Flow Simulator* plugin, that
is, some library interfacing with the *Flow Simulator Data Manager* (FSDM). The
*FSDM* is a C++ library wrapped to Python using *SWIG*, while for the plugin we
want to use *pybind11*. This sample code demonstrates how to pass some common
types (`FSMesh`, `FSClac`, `FSFloatArray`/`FSArrayPrimitiveT<FS_floatT>`)
between Python and and the C++ side of the plugin using *swigbind11*, while
automatically performing the necessary type conversions.

## Defining holder types and custom type casters

By default, *pybind11* uses `std::unique_ptr<T>` as a *holder type* for a given
C++ type `T`. The lifetime of objects created on the Python side or the C++ side
which are referenced also on the respective other side of the interface has to
be tracked carefully to avoid dangling references or issues with the Python GC.
To simplify this task for common use cases, *swigbind11* uses
`std::shared_ptr<T>` with a custom deleter as a holder type, which should support
proper lifetime tracking.

In order for `pybind11` to map C++ types to the exiting (but externally
defined) SWIG Python types and vise versa, it is necessary to set up
[custom type casters](https://pybind11.readthedocs.io/en/stable/advanced/cast/custom.html).
Instead of using the low-level functionality of *swigbind11* (i.e.,
`swig_py_cast` and `py_swig_cast`), the macro
`SWIGBIND11_TYPE_CASTER(cpp_type, python_type)` defined by *swigbind11* can be
used to set up the type casting between the C++ type `cpp_type` and the Python
type `python_type` taking into account the correct holder type,
`std::shared_ptr<cpp_type>`.

- `SWIGBIND11_TYPE_CASTER(cpp_type, python_type)`
- special case, e.g., `FSArray<>`:
  `SWIGBIND11_TYPE_CASTER_TWO_SIDED(cpp_type, to_swig, from_swig) `

Here, `FSArray<>` (and potentially other types) require special handling as the
SWIG layer introduces an intermediate type, resulting in distinct but
convertible types, depending on whether the array is create in Python or C++
(e.g., `FSFloatArray` vs. `FSArrayPrimitiveT<FS_floatT>`).
