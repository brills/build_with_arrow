#include "array_util.h"

#include <memory>

#include "arrow/api.h"
#include "arrow/c/abi.h"
#include "arrow/c/bridge.h"
#include "arrow/util/logging.h"

namespace my_ext {
std::shared_ptr<arrow::Array> GetSum(const std::shared_ptr<arrow::Array>& arr) {
  arrow::Int64Builder b;
  int64_t sum = 0;
  const auto a = static_cast<const arrow::Int64Array*>(arr.get());
  for (int64_t i = 0; i < a->length(); ++i) {
    sum += a->Value(i);
  }
  b.Append(sum);
  std::shared_ptr<arrow::Array> result;
  ARROW_CHECK_OK(b.Finish(&result));
  return result;
}

}  // namespace my_ext
