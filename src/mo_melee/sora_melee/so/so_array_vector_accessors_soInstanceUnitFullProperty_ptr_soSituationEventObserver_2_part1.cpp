#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soSituationEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soSituationEventObserver*>, 2>::size() const;
