#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soItemManageEventObserver;

template s32 soInstanceManagerFullPropertyVector<soItemManageEventObserver*, 1>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soItemManageEventObserver*, 1>::capacity();
template soItemManageEventObserver*& soInstanceManagerFullPropertyVector<soItemManageEventObserver*, 1>::atIndexFast(s32);
template soInstanceUnitFullProperty<soItemManageEventObserver*>& soInstanceManagerFullPropertyVector<soItemManageEventObserver*, 1>::atUnitIndexFast(s32);
