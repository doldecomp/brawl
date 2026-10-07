#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_array_value_soAnimCmdControlUnit.h>
#include <so/templates/so_instance_manager.h>
#pragma force_active on
class soAnimCmdControlUnit;

template soAttributeFlag soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, 7>::getAttribute(s32) const;
template void soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, 7>::getPriorityArray(soArray<soAnimCmdControlUnit*>&);
template s32 soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, 7>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, 7>::capacity();
template soAnimCmdControlUnit& soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, 7>::atIndexFast(s32);
template soInstanceUnitFullProperty<soAnimCmdControlUnit>& soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, 7>::atUnitIndexFast(s32);
template s32 soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, 7>::getIndex(s32) const;
