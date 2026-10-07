#pragma force_active off
#include <so/templates/so_instance_unit.h>
class ftEntryEventObserver;

template soInstanceUnitFullProperty<ftEntryEventObserver*>::soInstanceUnitFullProperty(ftEntryEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<ftEntryEventObserver*>::getAttribute() const;
