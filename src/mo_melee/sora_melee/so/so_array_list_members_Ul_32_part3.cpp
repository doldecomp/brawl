#pragma force_active on
#define SO_ARRAY_LIST_EXTERNAL_size
#define SO_ARRAY_LIST_EXTERNAL_capacity
#define SO_ARRAY_LIST_EXTERNAL_getArrayIndex
#include <so/so_array.h>

template u32 const& soArrayList<u32, 32>::at(s32) const;
template void soArrayList<u32, 32>::unshift(u32 const&);
template void soArrayList<u32, 32>::shift();
template void soArrayList<u32, 32>::push(u32 const&);
template void soArrayList<u32, 32>::pop();
template void soArrayList<u32, 32>::insert(s32,u32 const&);
template void soArrayList<u32, 32>::erase(s32);
template bool soArrayList<u32, 32>::isFull() const;
template void soArrayList<u32, 32>::set(s32,u32 const&,s32);
template bool soArrayList<u32, 32>::isNull() const;
template s32 soArrayList<u32, 32>::insertSub(s32,s32);
template void soArrayList<u32, 32>::eraseSub(s32);
template s32 soArrayList<u32, 32>::shiftFreeArrayIndex(s32);
