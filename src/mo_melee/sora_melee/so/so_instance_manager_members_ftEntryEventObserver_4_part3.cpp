#pragma force_active on
#include <so/templates/so_instance_manager.h>
class ftEntryEventObserver;

template s32 soInstanceManagerFullPropertyVector<ftEntryEventObserver*, 4>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<ftEntryEventObserver*, 4>::capacity();
template ftEntryEventObserver*& soInstanceManagerFullPropertyVector<ftEntryEventObserver*, 4>::atIndexFast(s32);
template soInstanceUnitFullProperty<ftEntryEventObserver*>& soInstanceManagerFullPropertyVector<ftEntryEventObserver*, 4>::atUnitIndexFast(s32);
