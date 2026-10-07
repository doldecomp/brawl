#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soModelEventObserver;

template soInstanceUnitFullProperty<soModelEventObserver*>::soInstanceUnitFullProperty(soModelEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soModelEventObserver*>::getAttribute() const;
