#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_ftSlotManager_FlexHeapInfo.h>

template s32 soArrayVector<ftSlotManager::FlexHeapInfo, 4>::getTopIndex() const;
template void soArrayVector<ftSlotManager::FlexHeapInfo, 4>::setTopIndex(s32);
template s32 soArrayVector<ftSlotManager::FlexHeapInfo, 4>::getLastIndex() const;
template void soArrayVector<ftSlotManager::FlexHeapInfo, 4>::setLastIndex(s32);
template ftSlotManager::FlexHeapInfo& soArrayVector<ftSlotManager::FlexHeapInfo, 4>::getArrayValueConst(s32);
template void soArrayVector<ftSlotManager::FlexHeapInfo, 4>::onFull();
template void soArrayVector<ftSlotManager::FlexHeapInfo, 4>::offFull();
template bool soArrayVector<ftSlotManager::FlexHeapInfo, 4>::isFull() const;
template s32 soArrayVector<ftSlotManager::FlexHeapInfo, 4>::capacity() const;
template ftSlotManager::FlexHeapInfo& soArrayVector<ftSlotManager::FlexHeapInfo, 4>::atFastAbstractSub(s32) const;
template void soArrayVector<ftSlotManager::FlexHeapInfo, 4>::setSize(s32);
