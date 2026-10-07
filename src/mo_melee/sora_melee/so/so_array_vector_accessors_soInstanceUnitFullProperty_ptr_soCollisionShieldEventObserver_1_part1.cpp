#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soCollisionShieldEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionShieldEventObserver*>, 1>::size() const;
