#pragma force_active off
#include <so/so_array.h>
#include <so/templates/so_damage.h>
#include <new>

typedef soArrayVector<soDamage, 1> VelaVec;

// MATCH-ONLY: constructing the vector forces the vtable and its adjustor thunks into this unit.
void vela_use(void* p) { new (p) VelaVec(); }
