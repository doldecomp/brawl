#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soCollisionCatchEventObserver;

template s32 soInstanceManagerFullPropertyVector<soCollisionCatchEventObserver*, 1>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soCollisionCatchEventObserver*, 1>::capacity();
template soCollisionCatchEventObserver*& soInstanceManagerFullPropertyVector<soCollisionCatchEventObserver*, 1>::atIndexFast(s32);
template soInstanceUnitFullProperty<soCollisionCatchEventObserver*>& soInstanceManagerFullPropertyVector<soCollisionCatchEventObserver*, 1>::atUnitIndexFast(s32);
