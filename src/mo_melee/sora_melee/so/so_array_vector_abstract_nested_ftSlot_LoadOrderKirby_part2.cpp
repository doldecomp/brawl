#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_ftSlot_LoadOrderKirby.h>

template ftSlot::LoadOrderKirby& soArrayVectorAbstract<ftSlot::LoadOrderKirby>::at(s32);
template const ftSlot::LoadOrderKirby& soArrayVectorAbstract<ftSlot::LoadOrderKirby>::at(s32) const;
template void soArrayVectorAbstract<ftSlot::LoadOrderKirby>::unshift(const ftSlot::LoadOrderKirby&);
template void soArrayVectorAbstract<ftSlot::LoadOrderKirby>::shift();
template void soArrayVectorAbstract<ftSlot::LoadOrderKirby>::pop();
template void soArrayVectorAbstract<ftSlot::LoadOrderKirby>::insert(s32, const ftSlot::LoadOrderKirby&);
template void soArrayVectorAbstract<ftSlot::LoadOrderKirby>::set(s32, const ftSlot::LoadOrderKirby&, s32);
template bool soArrayVectorAbstract<ftSlot::LoadOrderKirby>::isNull() const;
template void soArrayVectorAbstract<ftSlot::LoadOrderKirby>::substitution(s32, s32);
