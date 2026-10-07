#pragma force_active on
#include <so/templates/so_instance_manager.h>
class soCollisionReflectorEventObserver;

template s32 soInstanceManagerFullPropertyVector<soCollisionReflectorEventObserver*, 4>::getId(s32);
template u32 soInstanceManagerFullPropertyVector<soCollisionReflectorEventObserver*, 4>::capacity();
template soCollisionReflectorEventObserver*& soInstanceManagerFullPropertyVector<soCollisionReflectorEventObserver*, 4>::atIndexFast(s32);
template soInstanceUnitFullProperty<soCollisionReflectorEventObserver*>& soInstanceManagerFullPropertyVector<soCollisionReflectorEventObserver*, 4>::atUnitIndexFast(s32);
