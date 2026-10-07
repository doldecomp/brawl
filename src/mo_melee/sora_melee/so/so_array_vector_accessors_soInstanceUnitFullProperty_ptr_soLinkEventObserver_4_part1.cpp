#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soLinkEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soLinkEventObserver*>, 4>::size() const;
