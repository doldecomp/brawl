#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soArticleEventObserver;

template s32 soInstanceManagerFullPropertyVector<soArticleEventObserver*, 1>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soArticleEventObserver*, 1>::capacity();
template soArticleEventObserver*& soInstanceManagerFullPropertyVector<soArticleEventObserver*, 1>::atIndexFast(s32);
template soInstanceUnitFullProperty<soArticleEventObserver*>& soInstanceManagerFullPropertyVector<soArticleEventObserver*, 1>::atUnitIndexFast(s32);
