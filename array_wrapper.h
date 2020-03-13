#ifndef _ARRAY_WRAPPER_H_
#define _ARRAY_WRAPPER_H_
#include <memory>

#include "arrow/c/abi.h"
#include "arrow/c/helpers.h"
#include "arrow/result.h"

namespace arrow {
class Array;
} // namespace arrow

namespace my_ext {
class ArrayWrapper {
 public:
  ArrayWrapper() {}
  ~ArrayWrapper() {
    ArrowArrayRelease(&c_array_);
    ArrowSchemaRelease(&c_type_);
  }
  ArrayWrapper(const ArrayWrapper&) = delete;
  ArrayWrapper& operator=(const ArrayWrapper&) = delete;

  static arrow::Result<std::unique_ptr<ArrayWrapper>> Make(const arrow::Array& array);
  arrow::Result<std::shared_ptr<arrow::Array>> ToArrow();
  ArrowArray* c_array() {
    return &c_array_;
  }
  ArrowSchema* c_type() {
    return &c_type_;
  }
 private:
  ArrowArray c_array_ = {};
  ArrowSchema c_type_ = {};
};
}  // namespace my_ext
#endif  // _ARRAY_WRAPPER_H_
