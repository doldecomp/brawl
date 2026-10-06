#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soSlopeStatusParam.h>

template soSlopeStatusParam& soArrayVectorAbstract<soSlopeStatusParam>::at(s32);
template void soArrayVectorAbstract<soSlopeStatusParam>::push(const soSlopeStatusParam&);
template void soArrayVectorAbstract<soSlopeStatusParam>::clear();
