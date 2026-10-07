#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soTeamEventObserver;

template void soInstanceManagerFullPropertyVector<soTeamEventObserver*, 255>::set(soTeamEventObserver* const&, s32);
