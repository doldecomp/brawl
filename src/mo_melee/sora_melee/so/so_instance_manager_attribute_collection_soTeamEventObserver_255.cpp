#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soTeamEventObserver;

template void soInstanceManagerFullPropertyVector<soTeamEventObserver*, 255>::getAttributeArray(soAttributeFlag, soArray<soTeamEventObserver**>&);
