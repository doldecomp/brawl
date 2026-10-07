#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
#pragma force_active on
class soCollisionCatchEventObserver;

template void soInstanceManagerFullPropertyVector<soCollisionCatchEventObserver*, 1>::getPriorityArray(soArray<soCollisionCatchEventObserver**>&);
