#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_array_value_soAnimCmdControlUnit.h>
#include <so/templates/so_instance_manager.h>
class soAnimCmdControlUnit;

template void soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, 7>::erase(s32);
template void soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, 7>::clear();
