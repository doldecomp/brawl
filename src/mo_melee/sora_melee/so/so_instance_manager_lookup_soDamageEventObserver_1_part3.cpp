#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soDamageEventObserver;

template s32 soInstanceManagerFullPropertyVector<soDamageEventObserver*, 1>::getIndex(s32) const;
