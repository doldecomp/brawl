#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soCollisionSearchEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soCollisionSearchEventObserver*>, 2>::size() const;
