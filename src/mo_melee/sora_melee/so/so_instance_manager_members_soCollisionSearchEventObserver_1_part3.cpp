#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soCollisionSearchEventObserver;

template s32 soInstanceManagerFullPropertyVector<soCollisionSearchEventObserver*, 1>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soCollisionSearchEventObserver*, 1>::capacity();
template soCollisionSearchEventObserver*& soInstanceManagerFullPropertyVector<soCollisionSearchEventObserver*, 1>::atIndexFast(s32);
template soInstanceUnitFullProperty<soCollisionSearchEventObserver*>& soInstanceManagerFullPropertyVector<soCollisionSearchEventObserver*, 1>::atUnitIndexFast(s32);
