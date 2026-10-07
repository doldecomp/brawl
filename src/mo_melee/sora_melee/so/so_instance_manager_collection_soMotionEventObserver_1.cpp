#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
#pragma force_active on
class soMotionEventObserver;

template void soInstanceManagerFullPropertyVector<soMotionEventObserver*, 1>::getPriorityArray(soArray<soMotionEventObserver**>&);
