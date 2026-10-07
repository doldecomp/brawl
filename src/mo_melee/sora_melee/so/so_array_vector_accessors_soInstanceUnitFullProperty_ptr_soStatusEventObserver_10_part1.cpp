#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soStatusEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soStatusEventObserver*>, 10>::size() const;
