#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soSituationEventObserver;

template void soInstanceManagerFullPropertyVector<soSituationEventObserver*, 4>::set(soSituationEventObserver* const&, s32);
