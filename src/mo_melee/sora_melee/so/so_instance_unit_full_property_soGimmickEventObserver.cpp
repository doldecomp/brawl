#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soGimmickEventObserver;

template soInstanceUnitFullProperty<soGimmickEventObserver*>::soInstanceUnitFullProperty(soGimmickEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soGimmickEventObserver*>::getAttribute() const;
