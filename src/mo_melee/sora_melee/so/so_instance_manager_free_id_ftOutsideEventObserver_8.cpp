#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class ftOutsideEventObserver;

template s32 soInstanceManagerFullPropertyVector<ftOutsideEventObserver*, 8>::getFreeId() const;
