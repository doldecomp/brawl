#pragma force_active off
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soKineticEnergy;

template void soInstanceManagerFullPropertyVector<soKineticEnergy*, 12>::getAttributeArray(soAttributeFlag, soArray<soKineticEnergy**>&);
