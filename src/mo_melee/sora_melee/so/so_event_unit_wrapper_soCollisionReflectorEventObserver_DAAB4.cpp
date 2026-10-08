#pragma force_active off
#include <so/event/so_event_system.h>
#include <new>

class soCollisionReflectorEventObserver;

typedef soEventUnitWithWorkArea<soCollisionReflectorEventObserver, 4> Unit;

// MATCH-ONLY: constructing/deleting the unit forces its base-class members into this unit.
#pragma dont_inline on
void vela_use(void* p) { new (p) Unit(0, 0); }
void vela_del(Unit* p) { delete p; }
#pragma dont_inline reset
