#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soKineticEnergy;

template s32 soInstanceManagerFullPropertyVector<soKineticEnergy*, 4>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soKineticEnergy*, 4>::capacity();
template soKineticEnergy*& soInstanceManagerFullPropertyVector<soKineticEnergy*, 4>::atIndexFast(s32);
template soInstanceUnitFullProperty<soKineticEnergy*>& soInstanceManagerFullPropertyVector<soKineticEnergy*, 4>::atUnitIndexFast(s32);
