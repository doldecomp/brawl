#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_ftSlot_LoadOrder.h>

template void soArrayVectorAbstract<ftSlot::LoadOrder>::push(const ftSlot::LoadOrder&);
template void soArrayVectorAbstract<ftSlot::LoadOrder>::erase(s32);
template void soArrayVectorAbstract<ftSlot::LoadOrder>::clear();
