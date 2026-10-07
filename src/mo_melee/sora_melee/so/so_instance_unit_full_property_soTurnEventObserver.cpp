#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soTurnEventObserver;

template soInstanceUnitFullProperty<soTurnEventObserver*>::soInstanceUnitFullProperty(soTurnEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soTurnEventObserver*>::getAttribute() const;
