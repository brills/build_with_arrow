#include <memory>

#include "array_util.h"
#include "array_wrapper.h"
#include "arrow/array.h"
#include "pybind11/pybind11.h"
#include "Python.h"

namespace my_ext {
namespace {
std::shared_ptr<arrow::Array> UnwrapArray(ArrayWrapper* w) {
  auto r = w->ToArrow();
  if (!r.ok()) {
    throw std::runtime_error(r.status().ToString());
  }
  return std::move(r).ValueOrDie();
}

std::unique_ptr<ArrayWrapper> WrapArray(const arrow::Array& array) {
  auto r = ArrayWrapper::Make(array);
  if (!r.ok()) {
    throw std::runtime_error(r.status().ToString());
  }
  return std::move(r).ValueOrDie();
}

}  // namespace
namespace py = ::pybind11;

PYBIND11_MODULE(my_ext, m) {
  m.doc() = "My extension module";
  m.def("GetSum", [](ArrayWrapper* wrapper) -> std::unique_ptr<ArrayWrapper> {
    return WrapArray(*GetSum(UnwrapArray(wrapper)));
  });
  py::class_<ArrayWrapper>(m, "ArrayWrapper")
      .def(py::init([](py::object array) {
        auto result = std::unique_ptr<ArrayWrapper>(new ArrayWrapper);
        array.attr("_export_to_c")(result->c_array(), result->c_type());
//        PyObject* export_to_c_fun = PyObject_GetAttrString(
//            array.ptr(), "_export_to_c");
//        Py_XDECREF(PyObject_CallFunction(
//            export_to_c_fun, "KK", result->c_array(), result->c_type()));
//        Py_XDECREF(export_to_c_fun);
        return result;
      }))
      .def("_c_array",
           [](ArrayWrapper* w) {
             return reinterpret_cast<uintptr_t>(w->c_array());
           })
      .def("_c_type", [](ArrayWrapper* w) {
        return reinterpret_cast<uintptr_t>(w->c_type());
      })
      .def("ToArrow", [](ArrayWrapper* w) -> py::object {
        auto pyarrow_module = py::module::import("pyarrow");
        return pyarrow_module.attr("Array").attr("_import_from_c")(w->c_array(),
                                                                   w->c_type());
        //        PyObject* array_class = PyObject_GetAttrString(
        //            GetPyArrowModule(), "Array");
        //        PyObject* import_from_c_fun = PyObject_GetAttrString(
        //            array_class, "_import_from_c");
        //        auto result =
        //        py::reinterpret_steal<py::object>(PyObject_CallFunction(
        //            import_from_c_fun, "KK", w->c_array(), w->c_type()));
        //        Py_XDECREF(import_from_c_fun);
        //        Py_XDECREF(array_class);
        //        return result;
      });
}

}  // namespace my_ext
