#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soTeamEventObserver;

template s32 soInstanceManagerFullPropertyVector<soTeamEventObserver*, 255>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soTeamEventObserver*, 255>::capacity();
template soTeamEventObserver*& soInstanceManagerFullPropertyVector<soTeamEventObserver*, 255>::atIndexFast(s32);
template soInstanceUnitFullProperty<soTeamEventObserver*>& soInstanceManagerFullPropertyVector<soTeamEventObserver*, 255>::atUnitIndexFast(s32);
