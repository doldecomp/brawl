#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soTurnEventObserver;

template bool soInstanceManagerFullPropertyVector<soTurnEventObserver*, 8>::isContain(s32) const;
