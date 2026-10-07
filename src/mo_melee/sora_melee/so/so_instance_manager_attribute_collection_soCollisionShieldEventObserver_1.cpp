#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soCollisionShieldEventObserver;

template void soInstanceManagerFullPropertyVector<soCollisionShieldEventObserver*, 1>::getAttributeArray(soAttributeFlag, soArray<soCollisionShieldEventObserver**>&);
