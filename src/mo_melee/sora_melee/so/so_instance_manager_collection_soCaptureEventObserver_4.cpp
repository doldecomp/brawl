#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
#pragma force_active on
class soCaptureEventObserver;

template void soInstanceManagerFullPropertyVector<soCaptureEventObserver*, 4>::getPriorityArray(soArray<soCaptureEventObserver**>&);
