#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#define SO_INSTANCE_MANAGER_EXTERNAL_FREE_ID
#define SO_INSTANCE_MANAGER_EXTERNAL_IS_CONTAIN
#include <so/templates/so_instance_manager.h>
class soGimmickEventObserver;

template s32 soInstanceManagerFullPropertyVector<soGimmickEventObserver*, 8>::add(soGimmickEventObserver*&, s32, soAttributeFlag, s16);
