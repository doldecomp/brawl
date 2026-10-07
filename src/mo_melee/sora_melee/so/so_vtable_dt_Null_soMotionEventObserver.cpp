#pragma force_active off
#include <so/templates/so_instance_manager.h>
#include <new>

class soMotionEventObserver;

typedef soInstanceManagerFullPropertyNull<soMotionEventObserver*> Obj;

// MATCH-ONLY: constructing the object forces its vtable and special members into this unit.
#pragma dont_inline on
void vela_use(void* p) { new (p) Obj(); }
#pragma dont_inline reset
#pragma dont_inline on
void vela_del(Obj* p) { delete p; }
#pragma dont_inline reset
