#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soCaptureEventObserver;

template s32 soInstanceManagerFullPropertyVector<soCaptureEventObserver*, 4>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soCaptureEventObserver*, 4>::capacity();
template soCaptureEventObserver*& soInstanceManagerFullPropertyVector<soCaptureEventObserver*, 4>::atIndexFast(s32);
template soInstanceUnitFullProperty<soCaptureEventObserver*>& soInstanceManagerFullPropertyVector<soCaptureEventObserver*, 4>::atUnitIndexFast(s32);
