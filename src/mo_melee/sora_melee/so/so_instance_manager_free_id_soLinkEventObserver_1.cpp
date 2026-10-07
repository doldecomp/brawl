#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soLinkEventObserver;

template s32 soInstanceManagerFullPropertyVector<soLinkEventObserver*, 1>::getFreeId() const;
