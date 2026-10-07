#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soSituationEventObserver;

template void soInstanceManagerFullPropertyVector<soSituationEventObserver*, 1>::getAttributeArray(soAttributeFlag, soArray<soSituationEventObserver**>&);
