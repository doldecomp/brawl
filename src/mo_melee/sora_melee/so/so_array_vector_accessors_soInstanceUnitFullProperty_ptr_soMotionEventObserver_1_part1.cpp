#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soMotionEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soMotionEventObserver*>, 1>::size() const;
