#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soStatusEventObserver;

template soInstanceUnitFullProperty<soStatusEventObserver*>::soInstanceUnitFullProperty(soStatusEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soStatusEventObserver*>::getAttribute() const;
