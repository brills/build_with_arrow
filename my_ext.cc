#include <memory>
#include <iostream>

#include "arrow/c/abi.h"
#include "arrow/c/bridge.h"
#include "arrow/c/helpers.h"
#include "array_util.h"
#include "arrow/array.h"
#include "pybind11/pybind11.h"

namespace {

class ArrayWrapper {
 public:
  explicit ArrayWrapper(const arrow::Array& arr) : c_array_{}, c_type_{} {
    auto r = arrow::ExportArray(arr, &c_array_, &c_type_);
    if (!r.ok()) {
      throw std::runtime_error(r.ToString());
    }
  }
  ArrayWrapper() {}

  ~ArrayWrapper() {
    ArrowArrayRelease(&c_array_);
    ArrowSchemaRelease(&c_type_);
  }
  ArrayWrapper(const ArrayWrapper&) = delete;
  ArrayWrapper& operator=(const ArrayWrapper&) = delete;

  std::shared_ptr<arrow::Array> ToArrow() {
    auto r = arrow::ImportArray(&c_array_, &c_type_);
    if (!r.ok()) {
      throw std::runtime_error(r.status().ToString());
    }
    return r.ValueOrDie();
  }
  uintptr_t c_array_as_int() {
    return reinterpret_cast<uintptr_t>(&c_array_);
  }
  uintptr_t c_type_as_int() {
    return reinterpret_cast<uintptr_t>(&c_type_);
  }
 private:
  ArrowArray c_array_ = {};
  ArrowSchema c_type_ = {};
};

}  // namespace

namespace pybind11 {
namespace detail {
template <>
struct type_caster<std::shared_ptr<arrow::Array>> {
 public:
  PYBIND11_TYPE_CASTER(std::shared_ptr<arrow::Array>,
                       _<std::shared_ptr<arrow::Array>>());

  bool load(handle src, bool unused_implicit_conversion) {
    ArrayWrapper w;
    src.attr("_export_to_c")((w.c_array_as_int()),
                             (w.c_type_as_int()));
    value = w.ToArrow();
    return true;
  }

  static handle cast(const std::shared_ptr<arrow::Array>& src,
                     return_value_policy unused_return_value_policy,
                     handle unused_handle) {
    ArrowArray c_array;
    ArrowSchema c_type;
    if (!arrow::ExportArray(*src, &c_array, &c_type).ok()) {
      throw std::runtime_error("Unable to ExportArray");
    }
    ArrayWrapper w(*src);
    auto pyarrow_module = module::import("pyarrow");
    auto py_arr = pyarrow_module.attr("Array").attr("_import_from_c")(
        w.c_array_as_int(),
        w.c_type_as_int());
    return py_arr.release();
  }
};

}
}

namespace my_ext {
namespace py = ::pybind11;

PYBIND11_MODULE(my_ext, m) {
  m.doc() = "My extension module";
  m.def("GetSum", &GetSum);
}

}  // namespace my_ext
