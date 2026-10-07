#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soDisposeInstanceEventObserver;

template soInstanceUnitFullProperty<soDisposeInstanceEventObserver*>::soInstanceUnitFullProperty(soDisposeInstanceEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soDisposeInstanceEventObserver*>::getAttribute() const;
