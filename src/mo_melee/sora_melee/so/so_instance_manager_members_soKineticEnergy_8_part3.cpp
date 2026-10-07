#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soKineticEnergy;

template s32 soInstanceManagerFullPropertyVector<soKineticEnergy*, 8>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soKineticEnergy*, 8>::capacity();
template soKineticEnergy*& soInstanceManagerFullPropertyVector<soKineticEnergy*, 8>::atIndexFast(s32);
template soInstanceUnitFullProperty<soKineticEnergy*>& soInstanceManagerFullPropertyVector<soKineticEnergy*, 8>::atUnitIndexFast(s32);
