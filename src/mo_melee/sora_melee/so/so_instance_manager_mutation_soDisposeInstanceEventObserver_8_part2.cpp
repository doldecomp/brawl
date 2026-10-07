#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soDisposeInstanceEventObserver;

template void soInstanceManagerFullPropertyVector<soDisposeInstanceEventObserver*, 8>::set(soDisposeInstanceEventObserver* const&, s32);
