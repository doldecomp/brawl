#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soTurnEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soTurnEventObserver*>, 6>::size() const;
