#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soCollisionSearchEventObserver;

template soInstanceUnitFullProperty<soCollisionSearchEventObserver*>::soInstanceUnitFullProperty(soCollisionSearchEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soCollisionSearchEventObserver*>::getAttribute() const;
