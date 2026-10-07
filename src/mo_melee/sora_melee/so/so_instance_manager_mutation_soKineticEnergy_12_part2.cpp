#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#define SO_INSTANCE_MANAGER_EXTERNAL_AT
#include <so/templates/so_instance_manager.h>
class soKineticEnergy;

template void soInstanceManagerFullPropertyVector<soKineticEnergy*, 12>::set(soKineticEnergy* const&, s32);
