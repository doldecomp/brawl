#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soCollisionReflectorEventObserver;

template s32 soInstanceManagerFullPropertyVector<soCollisionReflectorEventObserver*, 1>::getFreeId() const;
