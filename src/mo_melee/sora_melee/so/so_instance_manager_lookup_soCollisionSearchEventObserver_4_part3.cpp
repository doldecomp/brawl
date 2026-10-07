#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soCollisionSearchEventObserver;

template s32 soInstanceManagerFullPropertyVector<soCollisionSearchEventObserver*, 4>::getIndex(s32) const;
