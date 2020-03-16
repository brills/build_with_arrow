import pyarrow as pa
import my_ext
import sys

s = my_ext.GetSum(pa.array([1,2,3], type=pa.int64()))
assert s.equals(pa.array([6]))
assert sys.getrefcount(s) == 2
print("PASSED")

