#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soCollisionAbsorberEventObserver;

template s32 soInstanceManagerFullPropertyVector<soCollisionAbsorberEventObserver*, 4>::getFreeId() const;
