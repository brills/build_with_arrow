# build_with_arrow
Demonstrate usage of pyarrow's C bridge. 

A python extension that linked statically against Arrow C++ source, but can talk with pyarrow.

`ext.cc` contains most of the juice (a pybind11 caster that invokes pyarrow's C bridge).
