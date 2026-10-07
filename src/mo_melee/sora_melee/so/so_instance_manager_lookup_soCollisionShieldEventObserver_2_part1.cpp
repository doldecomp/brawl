#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soCollisionShieldEventObserver;

template soCollisionShieldEventObserver*& soInstanceManagerFullPropertyVector<soCollisionShieldEventObserver*, 2>::at(s32);
