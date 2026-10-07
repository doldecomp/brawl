#pragma force_active off
#include <so/templates/so_array_value_soAnimCmdControlUnit.h>
#include <so/templates/so_instance_manager.h>
#pragma force_active on
class soAnimCmdControlUnit;

template u32 soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, 7>::size() const;
template bool soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, 7>::isContain(s32) const;
