#pragma force_active on
#include <so/so_array.h>

template s32 soArrayVector<soGeneralFlag<s32>, 16>::getTopIndex() const;
template s32 soArrayVector<soGeneralFlag<s32>, 16>::getLastIndex() const;
template bool soArrayVector<soGeneralFlag<s32>, 16>::isFull() const;
template s32 soArrayVector<soGeneralFlag<s32>, 16>::capacity() const;
