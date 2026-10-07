#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soDisposeInstanceEventObserver;

template s32 soInstanceManagerFullPropertyVector<soDisposeInstanceEventObserver*, 8>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soDisposeInstanceEventObserver*, 8>::capacity();
template soDisposeInstanceEventObserver*& soInstanceManagerFullPropertyVector<soDisposeInstanceEventObserver*, 8>::atIndexFast(s32);
template soInstanceUnitFullProperty<soDisposeInstanceEventObserver*>& soInstanceManagerFullPropertyVector<soDisposeInstanceEventObserver*, 8>::atUnitIndexFast(s32);
