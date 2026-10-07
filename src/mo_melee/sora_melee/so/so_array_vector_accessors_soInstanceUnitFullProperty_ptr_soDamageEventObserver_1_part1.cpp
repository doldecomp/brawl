#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soDamageEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soDamageEventObserver*>, 1>::size() const;
