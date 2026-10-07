#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soCaptureEventObserver;

template void soInstanceManagerFullPropertyVector<soCaptureEventObserver*, 1>::getAttributeArray(soAttributeFlag, soArray<soCaptureEventObserver**>&);
