#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soAnimCmdAddressPack.h>

template soAnimCmdAddressPack& soArrayVectorAbstract<soAnimCmdAddressPack>::at(s32);
template const soAnimCmdAddressPack& soArrayVectorAbstract<soAnimCmdAddressPack>::at(s32) const;
template void soArrayVectorAbstract<soAnimCmdAddressPack>::unshift(const soAnimCmdAddressPack&);
template void soArrayVectorAbstract<soAnimCmdAddressPack>::shift();
template void soArrayVectorAbstract<soAnimCmdAddressPack>::push(const soAnimCmdAddressPack&);
