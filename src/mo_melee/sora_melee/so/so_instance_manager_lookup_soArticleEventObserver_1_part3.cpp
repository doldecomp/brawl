#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soArticleEventObserver;

template s32 soInstanceManagerFullPropertyVector<soArticleEventObserver*, 1>::getIndex(s32) const;
