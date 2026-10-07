#pragma force_active off
#include <so/templates/so_instance_manager.h>
#include <new>

class soAnimCmdEventObserver;

typedef soInstanceManagerFullPropertyVector<soAnimCmdEventObserver*, 32> Mgr;

// MATCH-ONLY: constructing the manager forces the vtable and its adjustor thunks into this unit.
void vela_use(void* p) { new (p) Mgr(); }
