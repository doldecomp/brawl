#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soCaptureEventObserver;

template s32 soInstanceManagerFullPropertyVector<soCaptureEventObserver*, 1>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soCaptureEventObserver*, 1>::capacity();
template soCaptureEventObserver*& soInstanceManagerFullPropertyVector<soCaptureEventObserver*, 1>::atIndexFast(s32);
template soInstanceUnitFullProperty<soCaptureEventObserver*>& soInstanceManagerFullPropertyVector<soCaptureEventObserver*, 1>::atUnitIndexFast(s32);
