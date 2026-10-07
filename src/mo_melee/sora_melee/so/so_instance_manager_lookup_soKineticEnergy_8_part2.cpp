#pragma force_active on
#define SO_INSTANCE_MANAGER_EXTERNAL_SIZE
#include <so/templates/so_instance_manager.h>
class soKineticEnergy;

template bool soInstanceManagerFullPropertyVector<soKineticEnergy*, 8>::isContain(s32) const;
