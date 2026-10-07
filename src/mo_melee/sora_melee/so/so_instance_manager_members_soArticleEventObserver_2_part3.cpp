#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soArticleEventObserver;

template s32 soInstanceManagerFullPropertyVector<soArticleEventObserver*, 2>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soArticleEventObserver*, 2>::capacity();
template soArticleEventObserver*& soInstanceManagerFullPropertyVector<soArticleEventObserver*, 2>::atIndexFast(s32);
template soInstanceUnitFullProperty<soArticleEventObserver*>& soInstanceManagerFullPropertyVector<soArticleEventObserver*, 2>::atUnitIndexFast(s32);
