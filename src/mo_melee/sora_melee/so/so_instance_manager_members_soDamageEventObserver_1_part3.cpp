#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soDamageEventObserver;

template s32 soInstanceManagerFullPropertyVector<soDamageEventObserver*, 1>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soDamageEventObserver*, 1>::capacity();
template soDamageEventObserver*& soInstanceManagerFullPropertyVector<soDamageEventObserver*, 1>::atIndexFast(s32);
template soInstanceUnitFullProperty<soDamageEventObserver*>& soInstanceManagerFullPropertyVector<soDamageEventObserver*, 1>::atUnitIndexFast(s32);
