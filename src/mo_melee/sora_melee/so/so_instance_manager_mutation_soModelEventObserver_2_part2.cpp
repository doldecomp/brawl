#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soModelEventObserver;

template void soInstanceManagerFullPropertyVector<soModelEventObserver*, 2>::set(soModelEventObserver* const&, s32);
