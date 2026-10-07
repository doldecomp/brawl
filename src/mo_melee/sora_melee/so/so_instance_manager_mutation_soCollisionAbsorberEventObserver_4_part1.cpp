#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soCollisionAbsorberEventObserver;

template void soInstanceManagerFullPropertyVector<soCollisionAbsorberEventObserver*, 4>::erase(s32);
template void soInstanceManagerFullPropertyVector<soCollisionAbsorberEventObserver*, 4>::clear();
