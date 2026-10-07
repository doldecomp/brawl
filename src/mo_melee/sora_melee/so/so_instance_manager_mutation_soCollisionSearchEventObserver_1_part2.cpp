#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soCollisionSearchEventObserver;

template void soInstanceManagerFullPropertyVector<soCollisionSearchEventObserver*, 1>::set(soCollisionSearchEventObserver* const&, s32);
