#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soCollisionHitEventObserver;

template s32 soInstanceManagerFullPropertyVector<soCollisionHitEventObserver*, 1>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soCollisionHitEventObserver*, 1>::capacity();
template soCollisionHitEventObserver*& soInstanceManagerFullPropertyVector<soCollisionHitEventObserver*, 1>::atIndexFast(s32);
template soInstanceUnitFullProperty<soCollisionHitEventObserver*>& soInstanceManagerFullPropertyVector<soCollisionHitEventObserver*, 1>::atUnitIndexFast(s32);
