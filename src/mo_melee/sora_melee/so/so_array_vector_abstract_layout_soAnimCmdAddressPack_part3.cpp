#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soAnimCmdAddressPack.h>

template void soArrayVectorAbstract<soAnimCmdAddressPack>::set(s32, const soAnimCmdAddressPack&, s32);
template void soArrayVectorAbstract<soAnimCmdAddressPack>::clear();
template bool soArrayVectorAbstract<soAnimCmdAddressPack>::isNull() const;
template void soArrayVectorAbstract<soAnimCmdAddressPack>::substitution(s32, s32);
