#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soAnimCmdEventObserver;

template soInstanceUnitFullProperty<soAnimCmdEventObserver*>::soInstanceUnitFullProperty(soAnimCmdEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soAnimCmdEventObserver*>::getAttribute() const;
