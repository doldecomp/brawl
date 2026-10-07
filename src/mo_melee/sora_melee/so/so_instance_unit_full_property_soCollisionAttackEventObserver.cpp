#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soCollisionAttackEventObserver;

template soInstanceUnitFullProperty<soCollisionAttackEventObserver*>::soInstanceUnitFullProperty(soCollisionAttackEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soCollisionAttackEventObserver*>::getAttribute() const;
