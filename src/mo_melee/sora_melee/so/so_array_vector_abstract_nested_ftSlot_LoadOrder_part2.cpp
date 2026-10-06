#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_ftSlot_LoadOrder.h>

template ftSlot::LoadOrder& soArrayVectorAbstract<ftSlot::LoadOrder>::at(s32);
template const ftSlot::LoadOrder& soArrayVectorAbstract<ftSlot::LoadOrder>::at(s32) const;
template void soArrayVectorAbstract<ftSlot::LoadOrder>::unshift(const ftSlot::LoadOrder&);
template void soArrayVectorAbstract<ftSlot::LoadOrder>::shift();
template void soArrayVectorAbstract<ftSlot::LoadOrder>::pop();
template void soArrayVectorAbstract<ftSlot::LoadOrder>::insert(s32, const ftSlot::LoadOrder&);
template void soArrayVectorAbstract<ftSlot::LoadOrder>::set(s32, const ftSlot::LoadOrder&, s32);
template bool soArrayVectorAbstract<ftSlot::LoadOrder>::isNull() const;
template void soArrayVectorAbstract<ftSlot::LoadOrder>::substitution(s32, s32);
