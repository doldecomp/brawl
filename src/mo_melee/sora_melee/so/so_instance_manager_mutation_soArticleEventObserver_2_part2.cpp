#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soArticleEventObserver;

template void soInstanceManagerFullPropertyVector<soArticleEventObserver*, 2>::set(soArticleEventObserver* const&, s32);
