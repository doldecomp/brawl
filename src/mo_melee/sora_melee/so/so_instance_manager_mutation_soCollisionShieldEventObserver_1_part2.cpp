#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soCollisionShieldEventObserver;

template void soInstanceManagerFullPropertyVector<soCollisionShieldEventObserver*, 1>::set(soCollisionShieldEventObserver* const&, s32);
