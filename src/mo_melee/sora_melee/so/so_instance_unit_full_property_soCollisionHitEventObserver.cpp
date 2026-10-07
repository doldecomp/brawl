#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soCollisionHitEventObserver;

template soInstanceUnitFullProperty<soCollisionHitEventObserver*>::soInstanceUnitFullProperty(soCollisionHitEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soCollisionHitEventObserver*>::getAttribute() const;
