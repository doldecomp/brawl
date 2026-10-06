#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soSlopeStatusParam.h>

template const soSlopeStatusParam& soArrayVectorAbstract<soSlopeStatusParam>::at(s32) const;
template void soArrayVectorAbstract<soSlopeStatusParam>::unshift(const soSlopeStatusParam&);
template void soArrayVectorAbstract<soSlopeStatusParam>::shift();
template void soArrayVectorAbstract<soSlopeStatusParam>::pop();
template void soArrayVectorAbstract<soSlopeStatusParam>::insert(s32, const soSlopeStatusParam&);
template void soArrayVectorAbstract<soSlopeStatusParam>::erase(s32);
template void soArrayVectorAbstract<soSlopeStatusParam>::set(s32, const soSlopeStatusParam&, s32);
template bool soArrayVectorAbstract<soSlopeStatusParam>::isNull() const;
template void soArrayVectorAbstract<soSlopeStatusParam>::substitution(s32, s32);
