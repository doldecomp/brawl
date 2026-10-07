#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soCollisionAbsorberEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionAbsorberEventObserver*>, 4>::size() const;
