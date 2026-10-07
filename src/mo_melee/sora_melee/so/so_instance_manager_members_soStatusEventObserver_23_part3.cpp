#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soStatusEventObserver;

template s32 soInstanceManagerFullPropertyVector<soStatusEventObserver*, 23>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soStatusEventObserver*, 23>::capacity();
template soStatusEventObserver*& soInstanceManagerFullPropertyVector<soStatusEventObserver*, 23>::atIndexFast(s32);
template soInstanceUnitFullProperty<soStatusEventObserver*>& soInstanceManagerFullPropertyVector<soStatusEventObserver*, 23>::atUnitIndexFast(s32);
