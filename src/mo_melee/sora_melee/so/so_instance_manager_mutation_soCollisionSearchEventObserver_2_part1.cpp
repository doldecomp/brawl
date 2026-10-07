#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soCollisionSearchEventObserver;

template void soInstanceManagerFullPropertyVector<soCollisionSearchEventObserver*, 2>::erase(s32);
template void soInstanceManagerFullPropertyVector<soCollisionSearchEventObserver*, 2>::clear();
