#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soMotionEventObserver;

template soInstanceUnitFullProperty<soMotionEventObserver*>::soInstanceUnitFullProperty(soMotionEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soMotionEventObserver*>::getAttribute() const;
