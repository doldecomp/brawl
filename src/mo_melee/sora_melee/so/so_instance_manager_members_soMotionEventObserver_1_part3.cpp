#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soMotionEventObserver;

template s32 soInstanceManagerFullPropertyVector<soMotionEventObserver*, 1>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soMotionEventObserver*, 1>::capacity();
template soMotionEventObserver*& soInstanceManagerFullPropertyVector<soMotionEventObserver*, 1>::atIndexFast(s32);
template soInstanceUnitFullProperty<soMotionEventObserver*>& soInstanceManagerFullPropertyVector<soMotionEventObserver*, 1>::atUnitIndexFast(s32);
