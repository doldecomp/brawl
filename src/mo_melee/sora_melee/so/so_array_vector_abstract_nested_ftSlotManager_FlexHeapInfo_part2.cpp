#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_ftSlotManager_FlexHeapInfo.h>

template ftSlotManager::FlexHeapInfo& soArrayVectorAbstract<ftSlotManager::FlexHeapInfo>::at(s32);
template const ftSlotManager::FlexHeapInfo& soArrayVectorAbstract<ftSlotManager::FlexHeapInfo>::at(s32) const;
template void soArrayVectorAbstract<ftSlotManager::FlexHeapInfo>::unshift(const ftSlotManager::FlexHeapInfo&);
template void soArrayVectorAbstract<ftSlotManager::FlexHeapInfo>::shift();
template void soArrayVectorAbstract<ftSlotManager::FlexHeapInfo>::pop();
template void soArrayVectorAbstract<ftSlotManager::FlexHeapInfo>::insert(s32, const ftSlotManager::FlexHeapInfo&);
template void soArrayVectorAbstract<ftSlotManager::FlexHeapInfo>::set(s32, const ftSlotManager::FlexHeapInfo&, s32);
template bool soArrayVectorAbstract<ftSlotManager::FlexHeapInfo>::isNull() const;
template void soArrayVectorAbstract<ftSlotManager::FlexHeapInfo>::substitution(s32, s32);
