#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
#pragma force_active on
class soItemManageEventObserver;

template void soInstanceManagerFullPropertyVector<soItemManageEventObserver*, 1>::getPriorityArray(soArray<soItemManageEventObserver**>&);
