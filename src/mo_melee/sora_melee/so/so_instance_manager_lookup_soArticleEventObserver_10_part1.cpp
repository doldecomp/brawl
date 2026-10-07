#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soArticleEventObserver;

template soArticleEventObserver*& soInstanceManagerFullPropertyVector<soArticleEventObserver*, 10>::at(s32);
