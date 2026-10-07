#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soModelEventObserver;

template s32 soInstanceManagerFullPropertyVector<soModelEventObserver*, 3>::getIndex(s32) const;
