#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soLogAttackInfo.h>

template void soArrayVectorAbstract<soLogAttackInfo>::unshift(const soLogAttackInfo&);
template void soArrayVectorAbstract<soLogAttackInfo>::pop();
template void soArrayVectorAbstract<soLogAttackInfo>::clear();
