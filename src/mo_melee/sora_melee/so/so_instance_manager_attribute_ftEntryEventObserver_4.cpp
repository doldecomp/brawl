#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class ftEntryEventObserver;

template soAttributeFlag soInstanceManagerFullPropertyVector<ftEntryEventObserver*, 4>::getAttribute(s32) const;
