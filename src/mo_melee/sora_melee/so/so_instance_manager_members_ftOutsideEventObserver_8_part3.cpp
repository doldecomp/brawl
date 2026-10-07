#pragma force_active on
#include <so/templates/so_instance_manager.h>
class ftOutsideEventObserver;

template s32 soInstanceManagerFullPropertyVector<ftOutsideEventObserver*, 8>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<ftOutsideEventObserver*, 8>::capacity();
template ftOutsideEventObserver*& soInstanceManagerFullPropertyVector<ftOutsideEventObserver*, 8>::atIndexFast(s32);
template soInstanceUnitFullProperty<ftOutsideEventObserver*>& soInstanceManagerFullPropertyVector<ftOutsideEventObserver*, 8>::atUnitIndexFast(s32);
