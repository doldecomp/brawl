#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soCollisionAttackEventObserver;

template s32 soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 3>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 3>::capacity();
template soCollisionAttackEventObserver*& soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 3>::atIndexFast(s32);
template soInstanceUnitFullProperty<soCollisionAttackEventObserver*>& soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 3>::atUnitIndexFast(s32);
