#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soSituationEventObserver;

template soInstanceUnitFullProperty<soSituationEventObserver*>::soInstanceUnitFullProperty(soSituationEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soSituationEventObserver*>::getAttribute() const;
