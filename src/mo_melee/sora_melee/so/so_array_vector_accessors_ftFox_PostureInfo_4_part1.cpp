#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_ftFox_PostureInfo.h>

template s32 soArrayVector<ftFox::PostureInfo, 4>::getTopIndex() const;
template void soArrayVector<ftFox::PostureInfo, 4>::setTopIndex(s32);
template s32 soArrayVector<ftFox::PostureInfo, 4>::getLastIndex() const;
template void soArrayVector<ftFox::PostureInfo, 4>::setLastIndex(s32);
template ftFox::PostureInfo& soArrayVector<ftFox::PostureInfo, 4>::getArrayValueConst(s32);
template void soArrayVector<ftFox::PostureInfo, 4>::onFull();
template void soArrayVector<ftFox::PostureInfo, 4>::offFull();
template bool soArrayVector<ftFox::PostureInfo, 4>::isFull() const;
template s32 soArrayVector<ftFox::PostureInfo, 4>::capacity() const;
template s32 soArrayVector<ftFox::PostureInfo, 4>::size() const;
template void soArrayVector<ftFox::PostureInfo, 4>::setSize(s32);
