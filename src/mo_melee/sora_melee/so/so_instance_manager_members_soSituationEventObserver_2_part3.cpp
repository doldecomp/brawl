#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soSituationEventObserver;

template s32 soInstanceManagerFullPropertyVector<soSituationEventObserver*, 2>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soSituationEventObserver*, 2>::capacity();
template soSituationEventObserver*& soInstanceManagerFullPropertyVector<soSituationEventObserver*, 2>::atIndexFast(s32);
template soInstanceUnitFullProperty<soSituationEventObserver*>& soInstanceManagerFullPropertyVector<soSituationEventObserver*, 2>::atUnitIndexFast(s32);
