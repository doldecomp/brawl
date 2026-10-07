#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soCollisionReflectorEventObserver;

template soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>::soInstanceUnitFullProperty(soCollisionReflectorEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>::getAttribute() const;
