#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soTurnEventObserver;

template void soInstanceManagerFullPropertyVector<soTurnEventObserver*, 8>::set(soTurnEventObserver* const&, s32);
