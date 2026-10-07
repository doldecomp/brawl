#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soCollisionAttackEventObserver;

template s32 soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 2>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 2>::capacity();
template soCollisionAttackEventObserver*& soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 2>::atIndexFast(s32);
template soInstanceUnitFullProperty<soCollisionAttackEventObserver*>& soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 2>::atUnitIndexFast(s32);
