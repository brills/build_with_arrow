import my_ext
import pyarrow as pa

class ArrayWrapper(my_ext.ArrayWrapperBase):

  def __init__(self, array):
    super(ArrayWrapper, self).__init__()
    array._export_to_c(self._c_array(), self._c_type())

  def ToArrow(self):
    return pa.Array._import_from_c(self._c_array(), self._c_type())

