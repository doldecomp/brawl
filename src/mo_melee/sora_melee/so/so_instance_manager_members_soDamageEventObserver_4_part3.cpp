#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soDamageEventObserver;

template s32 soInstanceManagerFullPropertyVector<soDamageEventObserver*, 4>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soDamageEventObserver*, 4>::capacity();
template soDamageEventObserver*& soInstanceManagerFullPropertyVector<soDamageEventObserver*, 4>::atIndexFast(s32);
template soInstanceUnitFullProperty<soDamageEventObserver*>& soInstanceManagerFullPropertyVector<soDamageEventObserver*, 4>::atUnitIndexFast(s32);
