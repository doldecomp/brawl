#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soTeamEventObserver;

template soTeamEventObserver*& soInstanceManagerFullPropertyVector<soTeamEventObserver*, 255>::at(s32);
