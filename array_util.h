#ifndef _ARRAY_UTIL_H_
#define _ARRAY_UTIL_H_
#include <memory>

namespace arrow {
class Array;
}  // namespace arrow

namespace my_ext {
std::shared_ptr<arrow::Array> GetSum(const std::shared_ptr<arrow::Array>& arr);
}  // namespace my_ext

#endif  // _ARRAY_UTIL_H_
