#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soGimmickEventObserver;

template s32 soInstanceManagerFullPropertyVector<soGimmickEventObserver*, 8>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soGimmickEventObserver*, 8>::capacity();
template soGimmickEventObserver*& soInstanceManagerFullPropertyVector<soGimmickEventObserver*, 8>::atIndexFast(s32);
template soInstanceUnitFullProperty<soGimmickEventObserver*>& soInstanceManagerFullPropertyVector<soGimmickEventObserver*, 8>::atUnitIndexFast(s32);
