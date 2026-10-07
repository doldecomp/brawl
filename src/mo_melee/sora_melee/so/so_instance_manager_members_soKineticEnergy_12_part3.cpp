#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soKineticEnergy;

template s32 soInstanceManagerFullPropertyVector<soKineticEnergy*, 12>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soKineticEnergy*, 12>::capacity();
template soKineticEnergy*& soInstanceManagerFullPropertyVector<soKineticEnergy*, 12>::atIndexFast(s32);
template soInstanceUnitFullProperty<soKineticEnergy*>& soInstanceManagerFullPropertyVector<soKineticEnergy*, 12>::atUnitIndexFast(s32);
