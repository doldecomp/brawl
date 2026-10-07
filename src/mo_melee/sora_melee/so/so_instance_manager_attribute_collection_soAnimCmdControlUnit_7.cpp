#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_array_value_soAnimCmdControlUnit.h>
#include <so/templates/so_instance_manager.h>
class soAnimCmdControlUnit;

template void soInstanceManagerFullPropertyVector<soAnimCmdControlUnit, 7>::getAttributeArray(soAttributeFlag, soArray<soAnimCmdControlUnit*>&);
