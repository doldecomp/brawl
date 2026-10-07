#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soCollisionShieldEventObserver;

template s32 soInstanceManagerFullPropertyVector<soCollisionShieldEventObserver*, 1>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soCollisionShieldEventObserver*, 1>::capacity();
template soCollisionShieldEventObserver*& soInstanceManagerFullPropertyVector<soCollisionShieldEventObserver*, 1>::atIndexFast(s32);
template soInstanceUnitFullProperty<soCollisionShieldEventObserver*>& soInstanceManagerFullPropertyVector<soCollisionShieldEventObserver*, 1>::atUnitIndexFast(s32);
