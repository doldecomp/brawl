#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soTurnEventObserver;

template s32 soInstanceManagerFullPropertyVector<soTurnEventObserver*, 8>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soTurnEventObserver*, 8>::capacity();
template soTurnEventObserver*& soInstanceManagerFullPropertyVector<soTurnEventObserver*, 8>::atIndexFast(s32);
template soInstanceUnitFullProperty<soTurnEventObserver*>& soInstanceManagerFullPropertyVector<soTurnEventObserver*, 8>::atUnitIndexFast(s32);
