#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soSituationEventObserver;

template s32 soInstanceManagerFullPropertyVector<soSituationEventObserver*, 1>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soSituationEventObserver*, 1>::capacity();
template soSituationEventObserver*& soInstanceManagerFullPropertyVector<soSituationEventObserver*, 1>::atIndexFast(s32);
template soInstanceUnitFullProperty<soSituationEventObserver*>& soInstanceManagerFullPropertyVector<soSituationEventObserver*, 1>::atUnitIndexFast(s32);
