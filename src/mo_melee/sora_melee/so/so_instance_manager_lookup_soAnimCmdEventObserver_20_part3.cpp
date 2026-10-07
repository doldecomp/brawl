#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soAnimCmdEventObserver;

template s32 soInstanceManagerFullPropertyVector<soAnimCmdEventObserver*, 20>::getIndex(s32) const;
