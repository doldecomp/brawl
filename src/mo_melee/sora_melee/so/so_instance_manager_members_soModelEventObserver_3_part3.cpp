#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soModelEventObserver;

template s32 soInstanceManagerFullPropertyVector<soModelEventObserver*, 3>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soModelEventObserver*, 3>::capacity();
template soModelEventObserver*& soInstanceManagerFullPropertyVector<soModelEventObserver*, 3>::atIndexFast(s32);
template soInstanceUnitFullProperty<soModelEventObserver*>& soInstanceManagerFullPropertyVector<soModelEventObserver*, 3>::atUnitIndexFast(s32);
