#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soModelEventObserver;

template s32 soInstanceManagerFullPropertyVector<soModelEventObserver*, 1>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soModelEventObserver*, 1>::capacity();
template soModelEventObserver*& soInstanceManagerFullPropertyVector<soModelEventObserver*, 1>::atIndexFast(s32);
template soInstanceUnitFullProperty<soModelEventObserver*>& soInstanceManagerFullPropertyVector<soModelEventObserver*, 1>::atUnitIndexFast(s32);
