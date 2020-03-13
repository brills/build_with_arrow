import pyarrow as pa
import my_ext
import array_wrapper

arr = pa.array([1,2,3])
w_sum = my_ext.GetSum(array_wrapper.ArrayWrapper(arr))

assert pa.Array._import_from_c(w_sum._c_array(), w_sum._c_type()).equals(pa.array([6]))

