#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soCollisionShieldEventObserver;

template s32 soInstanceManagerFullPropertyVector<soCollisionShieldEventObserver*, 2>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soCollisionShieldEventObserver*, 2>::capacity();
template soCollisionShieldEventObserver*& soInstanceManagerFullPropertyVector<soCollisionShieldEventObserver*, 2>::atIndexFast(s32);
template soInstanceUnitFullProperty<soCollisionShieldEventObserver*>& soInstanceManagerFullPropertyVector<soCollisionShieldEventObserver*, 2>::atUnitIndexFast(s32);
