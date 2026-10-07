#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soCollisionAttackEventObserver;

template s32 soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 5>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 5>::capacity();
template soCollisionAttackEventObserver*& soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 5>::atIndexFast(s32);
template soInstanceUnitFullProperty<soCollisionAttackEventObserver*>& soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 5>::atUnitIndexFast(s32);
