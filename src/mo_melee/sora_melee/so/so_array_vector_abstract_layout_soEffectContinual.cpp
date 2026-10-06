#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soEffectContinual.h>

template soEffectContinual& soArrayVectorAbstract<soEffectContinual>::at(s32);
template const soEffectContinual& soArrayVectorAbstract<soEffectContinual>::at(s32) const;
template void soArrayVectorAbstract<soEffectContinual>::unshift(const soEffectContinual&);
template void soArrayVectorAbstract<soEffectContinual>::shift();
template void soArrayVectorAbstract<soEffectContinual>::push(const soEffectContinual&);
template void soArrayVectorAbstract<soEffectContinual>::pop();
template void soArrayVectorAbstract<soEffectContinual>::insert(s32, const soEffectContinual&);
template void soArrayVectorAbstract<soEffectContinual>::erase(s32);
template void soArrayVectorAbstract<soEffectContinual>::set(s32, const soEffectContinual&, s32);
template void soArrayVectorAbstract<soEffectContinual>::clear();
template bool soArrayVectorAbstract<soEffectContinual>::isNull() const;
template void soArrayVectorAbstract<soEffectContinual>::substitution(s32, s32);
