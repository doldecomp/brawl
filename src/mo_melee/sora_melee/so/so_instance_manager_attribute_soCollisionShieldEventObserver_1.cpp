#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soCollisionShieldEventObserver;

template soAttributeFlag soInstanceManagerFullPropertyVector<soCollisionShieldEventObserver*, 1>::getAttribute(s32) const;
