#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soCollisionShieldEventObserver;

template void soInstanceManagerFullPropertyVector<soCollisionShieldEventObserver*, 2>::erase(s32);
template void soInstanceManagerFullPropertyVector<soCollisionShieldEventObserver*, 2>::clear();
