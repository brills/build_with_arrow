#include "array_wrapper.h"
#include "arrow/c/bridge.h"

namespace my_ext {
arrow::Result<std::unique_ptr<ArrayWrapper>> ArrayWrapper::Make(const arrow::Array& array) {
  auto result = std::unique_ptr<ArrayWrapper>(new ArrayWrapper);
  ARROW_RETURN_NOT_OK(arrow::ExportArray(array, result->c_array(), result->c_type()));
  return result;
}

arrow::Result<std::shared_ptr<arrow::Array>> ArrayWrapper::ToArrow() {
  return arrow::ImportArray(c_array(), c_type());
}

}  // namespace my_ext
