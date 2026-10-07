#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soLinkEventObserver;

template soInstanceUnitFullProperty<soLinkEventObserver*>::soInstanceUnitFullProperty(soLinkEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soLinkEventObserver*>::getAttribute() const;
