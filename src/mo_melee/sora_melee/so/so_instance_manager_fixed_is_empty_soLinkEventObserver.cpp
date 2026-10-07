#pragma force_active off
#include <so/templates/so_instance_manager_fixed.h>
class soLinkEventObserver;

template bool soInstanceManagerFixed<soLinkEventObserver*>::isEmpty() const;
