#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soCollisionSearchEventObserver;

template s32 soInstanceManagerFullPropertyVector<soCollisionSearchEventObserver*, 2>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soCollisionSearchEventObserver*, 2>::capacity();
template soCollisionSearchEventObserver*& soInstanceManagerFullPropertyVector<soCollisionSearchEventObserver*, 2>::atIndexFast(s32);
template soInstanceUnitFullProperty<soCollisionSearchEventObserver*>& soInstanceManagerFullPropertyVector<soCollisionSearchEventObserver*, 2>::atUnitIndexFast(s32);
