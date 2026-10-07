#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soModelEventObserver;

template soAttributeFlag soInstanceManagerFullPropertyVector<soModelEventObserver*, 2>::getAttribute(s32) const;
