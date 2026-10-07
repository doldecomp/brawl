#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soDamageEventObserver;

template void soInstanceManagerFullPropertyVector<soDamageEventObserver*, 1>::set(soDamageEventObserver* const&, s32);
