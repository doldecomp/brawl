#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soSituationEventObserver;

template void soInstanceManagerFullPropertyVector<soSituationEventObserver*, 1>::erase(s32);
template void soInstanceManagerFullPropertyVector<soSituationEventObserver*, 1>::clear();
