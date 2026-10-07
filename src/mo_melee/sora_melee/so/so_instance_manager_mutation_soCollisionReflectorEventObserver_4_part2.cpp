#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soCollisionReflectorEventObserver;

template void soInstanceManagerFullPropertyVector<soCollisionReflectorEventObserver*, 4>::set(soCollisionReflectorEventObserver* const&, s32);
