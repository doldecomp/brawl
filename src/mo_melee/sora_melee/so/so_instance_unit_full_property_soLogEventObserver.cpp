#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soLogEventObserver;

template soInstanceUnitFullProperty<soLogEventObserver*>::soInstanceUnitFullProperty(soLogEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soLogEventObserver*>::getAttribute() const;
