# Example for *swigbind11*: FSPlugin using *pybind11*

This is the minimum working example of creating a *Flow Simulator* plugin, that
is, some library interfacing with the *Flow Simulator Data Manager* (FSDM). The
*FSDM* is a C++ library wrapped to Python using *SWIG*, while for the plugin we
want to use *pybind11*. This sample code demonstrates how to pass a `FSMesh`
object created in Python from the FSDM to the plugin by using *swigbind11* to
perform the necessary type conversion.