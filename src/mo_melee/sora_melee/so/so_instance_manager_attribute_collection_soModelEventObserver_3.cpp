#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soModelEventObserver;

template void soInstanceManagerFullPropertyVector<soModelEventObserver*, 3>::getAttributeArray(soAttributeFlag, soArray<soModelEventObserver**>&);
