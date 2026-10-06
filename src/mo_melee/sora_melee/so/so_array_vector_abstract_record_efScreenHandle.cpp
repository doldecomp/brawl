#pragma force_active on
#include <so/so_array.h>
#include <ef/ef_screen_handle.h>


template efScreenHandle& soArrayVectorAbstract<efScreenHandle>::at(s32);
template const efScreenHandle& soArrayVectorAbstract<efScreenHandle>::at(s32) const;
template void soArrayVectorAbstract<efScreenHandle>::unshift(const efScreenHandle&);
template void soArrayVectorAbstract<efScreenHandle>::shift();
template void soArrayVectorAbstract<efScreenHandle>::push(const efScreenHandle&);
template void soArrayVectorAbstract<efScreenHandle>::pop();
template void soArrayVectorAbstract<efScreenHandle>::insert(s32, const efScreenHandle&);
template void soArrayVectorAbstract<efScreenHandle>::erase(s32);
template void soArrayVectorAbstract<efScreenHandle>::set(s32, const efScreenHandle&, s32);
template void soArrayVectorAbstract<efScreenHandle>::clear();
template bool soArrayVectorAbstract<efScreenHandle>::isNull() const;
template void soArrayVectorAbstract<efScreenHandle>::substitution(s32, s32);
