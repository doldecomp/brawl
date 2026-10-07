#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soGimmickEventObserver;

template void soInstanceManagerFullPropertyVector<soGimmickEventObserver*, 8>::set(soGimmickEventObserver* const&, s32);
