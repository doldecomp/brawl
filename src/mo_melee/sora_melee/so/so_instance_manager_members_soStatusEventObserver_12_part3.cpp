#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soStatusEventObserver;

template s32 soInstanceManagerFullPropertyVector<soStatusEventObserver*, 12>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soStatusEventObserver*, 12>::capacity();
template soStatusEventObserver*& soInstanceManagerFullPropertyVector<soStatusEventObserver*, 12>::atIndexFast(s32);
template soInstanceUnitFullProperty<soStatusEventObserver*>& soInstanceManagerFullPropertyVector<soStatusEventObserver*, 12>::atUnitIndexFast(s32);
