#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soCollisionAttackEventObserver;

template void soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 5>::set(soCollisionAttackEventObserver* const&, s32);
