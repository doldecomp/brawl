#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soDamageEventObserver;

template soInstanceUnitFullProperty<soDamageEventObserver*>::soInstanceUnitFullProperty(soDamageEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soDamageEventObserver*>::getAttribute() const;
