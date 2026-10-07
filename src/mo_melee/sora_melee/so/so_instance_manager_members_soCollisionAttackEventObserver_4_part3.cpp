#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soCollisionAttackEventObserver;

template s32 soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 4>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 4>::capacity();
template soCollisionAttackEventObserver*& soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 4>::atIndexFast(s32);
template soInstanceUnitFullProperty<soCollisionAttackEventObserver*>& soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 4>::atUnitIndexFast(s32);
