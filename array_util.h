#ifndef _MY_EXT_ARRAY_UTIL_H_
#define _MY_EXT_ARRAY_UTIL_H_
#include <memory>

namespace arrow {
class Array;
}  // namespace arrow

namespace my_ext {
std::shared_ptr<arrow::Array> GetSum(const std::shared_ptr<arrow::Array>& arr);
}  // namespace

#endif  // _MY_EXT_ARRAY_UTIL_H_
