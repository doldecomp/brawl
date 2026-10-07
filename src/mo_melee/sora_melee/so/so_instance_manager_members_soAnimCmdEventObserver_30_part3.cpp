#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soAnimCmdEventObserver;

template s32 soInstanceManagerFullPropertyVector<soAnimCmdEventObserver*, 30>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soAnimCmdEventObserver*, 30>::capacity();
template soAnimCmdEventObserver*& soInstanceManagerFullPropertyVector<soAnimCmdEventObserver*, 30>::atIndexFast(s32);
template soInstanceUnitFullProperty<soAnimCmdEventObserver*>& soInstanceManagerFullPropertyVector<soAnimCmdEventObserver*, 30>::atUnitIndexFast(s32);
