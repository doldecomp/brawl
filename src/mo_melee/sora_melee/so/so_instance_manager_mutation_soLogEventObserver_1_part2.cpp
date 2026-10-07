#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soLogEventObserver;

template void soInstanceManagerFullPropertyVector<soLogEventObserver*, 1>::set(soLogEventObserver* const&, s32);
