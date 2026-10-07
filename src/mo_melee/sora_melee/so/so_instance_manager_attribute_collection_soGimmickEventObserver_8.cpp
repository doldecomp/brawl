#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soGimmickEventObserver;

template void soInstanceManagerFullPropertyVector<soGimmickEventObserver*, 8>::getAttributeArray(soAttributeFlag, soArray<soGimmickEventObserver**>&);
