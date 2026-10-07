#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soCollisionHitEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionHitEventObserver*>, 4>::size() const;
