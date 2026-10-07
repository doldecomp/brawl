#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soKineticEnergy;

template s32 soInstanceManagerFullPropertyVector<soKineticEnergy*, 2>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soKineticEnergy*, 2>::capacity();
template soKineticEnergy*& soInstanceManagerFullPropertyVector<soKineticEnergy*, 2>::atIndexFast(s32);
template soInstanceUnitFullProperty<soKineticEnergy*>& soInstanceManagerFullPropertyVector<soKineticEnergy*, 2>::atUnitIndexFast(s32);
