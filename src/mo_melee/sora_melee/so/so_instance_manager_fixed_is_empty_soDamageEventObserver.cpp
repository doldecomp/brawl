#pragma force_active off
#include <so/templates/so_instance_manager_fixed.h>
class soDamageEventObserver;

template bool soInstanceManagerFixed<soDamageEventObserver*>::isEmpty() const;
