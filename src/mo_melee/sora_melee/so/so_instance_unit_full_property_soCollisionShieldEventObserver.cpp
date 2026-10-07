#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soCollisionShieldEventObserver;

template soInstanceUnitFullProperty<soCollisionShieldEventObserver*>::soInstanceUnitFullProperty(soCollisionShieldEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soCollisionShieldEventObserver*>::getAttribute() const;
