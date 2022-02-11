swigbind11 - Interfacing SWIG and pybind11
==========================================

Many existing C++ codes use [*SWIG*](http://www.swig.org/) to automatically
generate bindings for Python, but over the last years
[*pybind11*](https://pybind11.readthedocs.io/) has gained a lot of popularity.
Most newer projects rely on *pybind11* and even large exiting code bases, such
as, *tensorflow*[^1], made the transition to *pybind11*. While SWIG is extremely
powerful with its support for a large number of languages, it has its
shortcomings w.r.t. supporting modern C++ standard. Development somewhat stalled
and with the increasing complexity of C++ it is unlikely SWIG will ever catch
up. The scope of *pybind11* is much more focused: the goal is to enable the
generation of Python bindings employing modern C++ itself. As such, *pybind11*
does not have to process and transform C++ code to generate the glue code for the
Python bindings, but rather *pybind11* provides a C++ library to enable the
developer to generate this glue code easily, as part of regular C++ library.

While creating Python modules using *pybind11* is surprisingly easy, things get
tricky when interacting with libraries using *SWIG* to generate their Python
bindings. As long as the modules generated via *SWIG* and *pybind11* interact
only on the Python level, the method the bindings were generated does not
matter. But as soon as a C++ library A wrapped to Python via *pybind11* tries to
interact with a library B wrapped to Python via *SWIG* by exchanging C++ objects
via the Python layer, incompatibilities arise due to the different methods of
wrapping the underlying C++ types.

To be continued....

[^1]: https://github.com/tensorflow/community/blob/master/rfcs/20190208-pybind11.md