#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soCollisionAttackEventObserver;

template void soInstanceManagerFullPropertyVector<soCollisionAttackEventObserver*, 5>::getAttributeArray(soAttributeFlag, soArray<soCollisionAttackEventObserver**>&);
