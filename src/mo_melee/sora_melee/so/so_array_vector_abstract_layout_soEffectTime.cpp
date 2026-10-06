#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soEffectTime.h>

template soEffectTime& soArrayVectorAbstract<soEffectTime>::at(s32);
template const soEffectTime& soArrayVectorAbstract<soEffectTime>::at(s32) const;
template void soArrayVectorAbstract<soEffectTime>::unshift(const soEffectTime&);
template void soArrayVectorAbstract<soEffectTime>::shift();
template void soArrayVectorAbstract<soEffectTime>::push(const soEffectTime&);
template void soArrayVectorAbstract<soEffectTime>::pop();
template void soArrayVectorAbstract<soEffectTime>::insert(s32, const soEffectTime&);
template void soArrayVectorAbstract<soEffectTime>::erase(s32);
template void soArrayVectorAbstract<soEffectTime>::set(s32, const soEffectTime&, s32);
template void soArrayVectorAbstract<soEffectTime>::clear();
template bool soArrayVectorAbstract<soEffectTime>::isNull() const;
template void soArrayVectorAbstract<soEffectTime>::substitution(s32, s32);
