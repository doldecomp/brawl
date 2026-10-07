#pragma force_active on
#define SO_ARRAY_LIST_EXTERNAL_isFull
#define SO_ARRAY_LIST_EXTERNAL_shiftFreeArrayIndex
#define SO_ARRAY_LIST_EXTERNAL_insertSub
#define SO_ARRAY_LIST_EXTERNAL_eraseSub
#include <so/so_array.h>

template u32& soArrayList<u32, 32>::at(s32);
template s32 soArrayList<u32, 32>::getArrayIndex(s32) const;
template s32 soArrayList<u32, 32>::size() const;
template s32 soArrayList<u32, 32>::capacity() const;
