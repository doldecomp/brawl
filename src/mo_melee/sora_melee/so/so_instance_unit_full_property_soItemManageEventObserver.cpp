#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soItemManageEventObserver;

template soInstanceUnitFullProperty<soItemManageEventObserver*>::soInstanceUnitFullProperty(soItemManageEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soItemManageEventObserver*>::getAttribute() const;
