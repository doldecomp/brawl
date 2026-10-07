#pragma force_active off
#include <so/templates/so_instance_manager_fixed.h>
class soMotionEventObserver;

template bool soInstanceManagerFixed<soMotionEventObserver*>::isEmpty() const;
