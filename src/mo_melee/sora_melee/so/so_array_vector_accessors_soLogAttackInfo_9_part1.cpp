#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soLogAttackInfo.h>

template bool soArrayVector<soLogAttackInfo, 9>::isFull() const;
template s32 soArrayVector<soLogAttackInfo, 9>::size() const;
