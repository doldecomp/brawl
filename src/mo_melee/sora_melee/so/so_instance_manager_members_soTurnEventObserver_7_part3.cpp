#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soTurnEventObserver;

template s32 soInstanceManagerFullPropertyVector<soTurnEventObserver*, 7>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soTurnEventObserver*, 7>::capacity();
template soTurnEventObserver*& soInstanceManagerFullPropertyVector<soTurnEventObserver*, 7>::atIndexFast(s32);
template soInstanceUnitFullProperty<soTurnEventObserver*>& soInstanceManagerFullPropertyVector<soTurnEventObserver*, 7>::atUnitIndexFast(s32);
