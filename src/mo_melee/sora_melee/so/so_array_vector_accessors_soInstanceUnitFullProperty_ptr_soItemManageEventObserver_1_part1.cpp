#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soItemManageEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soItemManageEventObserver*>, 1>::size() const;
