#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soModelEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soModelEventObserver*>, 4>::size() const;
