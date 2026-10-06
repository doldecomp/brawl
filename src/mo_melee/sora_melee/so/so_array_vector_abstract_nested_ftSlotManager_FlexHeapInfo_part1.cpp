#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_ftSlotManager_FlexHeapInfo.h>

template void soArrayVectorAbstract<ftSlotManager::FlexHeapInfo>::push(const ftSlotManager::FlexHeapInfo&);
template void soArrayVectorAbstract<ftSlotManager::FlexHeapInfo>::erase(s32);
template void soArrayVectorAbstract<ftSlotManager::FlexHeapInfo>::clear();
