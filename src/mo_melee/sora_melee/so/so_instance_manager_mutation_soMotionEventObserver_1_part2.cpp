#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soMotionEventObserver;

template void soInstanceManagerFullPropertyVector<soMotionEventObserver*, 1>::set(soMotionEventObserver* const&, s32);
