#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soCaptureEventObserver;

template s32 soArrayVector<soInstanceUnitFullProperty<soCaptureEventObserver*>, 4>::size() const;
