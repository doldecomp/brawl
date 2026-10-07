#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soCollisionCatchEventObserver;

template soInstanceUnitFullProperty<soCollisionCatchEventObserver*>::soInstanceUnitFullProperty(soCollisionCatchEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soCollisionCatchEventObserver*>::getAttribute() const;
