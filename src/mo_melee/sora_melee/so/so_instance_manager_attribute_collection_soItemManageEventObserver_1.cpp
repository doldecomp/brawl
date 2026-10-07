#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soItemManageEventObserver;

template void soInstanceManagerFullPropertyVector<soItemManageEventObserver*, 1>::getAttributeArray(soAttributeFlag, soArray<soItemManageEventObserver**>&);
