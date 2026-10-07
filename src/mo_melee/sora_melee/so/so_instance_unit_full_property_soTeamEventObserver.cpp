#pragma force_active off
#include <so/templates/so_instance_unit.h>
class soTeamEventObserver;

template soInstanceUnitFullProperty<soTeamEventObserver*>::soInstanceUnitFullProperty(soTeamEventObserver*&, s32, soAttributeFlag, s16);
template soAttributeFlag soInstanceUnitFullProperty<soTeamEventObserver*>::getAttribute() const;
