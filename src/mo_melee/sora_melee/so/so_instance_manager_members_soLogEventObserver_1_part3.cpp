#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soLogEventObserver;

template s32 soInstanceManagerFullPropertyVector<soLogEventObserver*, 1>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soLogEventObserver*, 1>::capacity();
template soLogEventObserver*& soInstanceManagerFullPropertyVector<soLogEventObserver*, 1>::atIndexFast(s32);
template soInstanceUnitFullProperty<soLogEventObserver*>& soInstanceManagerFullPropertyVector<soLogEventObserver*, 1>::atUnitIndexFast(s32);
