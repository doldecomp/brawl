#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soCollisionReflectorEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>, 1>::size() const;
