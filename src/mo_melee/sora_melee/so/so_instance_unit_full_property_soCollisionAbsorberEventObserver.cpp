#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soCollisionAbsorberEventObserver;

template soInstanceUnitFullProperty<soCollisionAbsorberEventObserver*>::soInstanceUnitFullProperty(soCollisionAbsorberEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soCollisionAbsorberEventObserver*>::getAttribute() const;
