#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soCollisionAttackEventObserver;

template bool soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 1>::isContain(s32) const;
