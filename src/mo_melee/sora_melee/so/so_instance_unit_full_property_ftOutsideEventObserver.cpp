#pragma force_active off
#include <so/templates/so_instance_unit.h>
class ftOutsideEventObserver;

template soInstanceUnitFullProperty<ftOutsideEventObserver*>::soInstanceUnitFullProperty(ftOutsideEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<ftOutsideEventObserver*>::getAttribute() const;
