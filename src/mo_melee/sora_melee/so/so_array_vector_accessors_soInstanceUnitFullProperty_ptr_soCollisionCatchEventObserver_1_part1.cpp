#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soCollisionCatchEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionCatchEventObserver*>, 1>::size() const;
