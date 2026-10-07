#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class ftOutsideEventObserver;

template void soInstanceManagerFullPropertyVector<ftOutsideEventObserver*, 8>::getAttributeArray(soAttributeFlag, soArray<ftOutsideEventObserver**>&);
