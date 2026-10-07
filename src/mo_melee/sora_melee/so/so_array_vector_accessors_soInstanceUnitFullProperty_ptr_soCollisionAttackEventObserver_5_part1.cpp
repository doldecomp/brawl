#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soCollisionAttackEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionAttackEventObserver*>, 5>::size() const;
