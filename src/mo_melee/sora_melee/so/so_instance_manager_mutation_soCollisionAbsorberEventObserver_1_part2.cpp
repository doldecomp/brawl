#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soCollisionAbsorberEventObserver;

template void soInstanceManagerFullPropertyVector<soCollisionAbsorberEventObserver*, 1>::set(soCollisionAbsorberEventObserver* const&, s32);
