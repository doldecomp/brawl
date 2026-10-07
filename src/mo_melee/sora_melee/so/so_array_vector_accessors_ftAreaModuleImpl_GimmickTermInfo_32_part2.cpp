#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_ftAreaModuleImpl_GimmickTermInfo.h>

template s32 soArrayVector<ftAreaModuleImpl::GimmickTermInfo, 32>::getTopIndex() const;
template void soArrayVector<ftAreaModuleImpl::GimmickTermInfo, 32>::setTopIndex(s32);
template s32 soArrayVector<ftAreaModuleImpl::GimmickTermInfo, 32>::getLastIndex() const;
template void soArrayVector<ftAreaModuleImpl::GimmickTermInfo, 32>::setLastIndex(s32);
template ftAreaModuleImpl::GimmickTermInfo& soArrayVector<ftAreaModuleImpl::GimmickTermInfo, 32>::getArrayValueConst(s32);
template void soArrayVector<ftAreaModuleImpl::GimmickTermInfo, 32>::onFull();
template void soArrayVector<ftAreaModuleImpl::GimmickTermInfo, 32>::offFull();
template bool soArrayVector<ftAreaModuleImpl::GimmickTermInfo, 32>::isFull() const;
template s32 soArrayVector<ftAreaModuleImpl::GimmickTermInfo, 32>::capacity() const;
template ftAreaModuleImpl::GimmickTermInfo& soArrayVector<ftAreaModuleImpl::GimmickTermInfo, 32>::atFastAbstractSub(s32) const;
template void soArrayVector<ftAreaModuleImpl::GimmickTermInfo, 32>::setSize(s32);
