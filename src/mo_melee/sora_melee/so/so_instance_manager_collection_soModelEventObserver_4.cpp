#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
#pragma force_active on
class soModelEventObserver;

template void soInstanceManagerFullPropertyVector<soModelEventObserver*, 4>::getPriorityArray(soArray<soModelEventObserver**>&);
