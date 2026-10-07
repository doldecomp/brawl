#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soDisposeInstanceEventObserver;

template void soInstanceManagerFullPropertyVector<soDisposeInstanceEventObserver*, 8>::getAttributeArray(soAttributeFlag, soArray<soDisposeInstanceEventObserver**>&);
