#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soGimmickEventObserver;

template s32 soInstanceManagerFullPropertyVector<soGimmickEventObserver*, 9>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soGimmickEventObserver*, 9>::capacity();
template soGimmickEventObserver*& soInstanceManagerFullPropertyVector<soGimmickEventObserver*, 9>::atIndexFast(s32);
template soInstanceUnitFullProperty<soGimmickEventObserver*>& soInstanceManagerFullPropertyVector<soGimmickEventObserver*, 9>::atUnitIndexFast(s32);
