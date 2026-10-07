#pragma force_active off
#include <so/so_array.h>
class wnPikminPikmin;
#include <new>

typedef soArrayVector<wnPikminPikmin*, 10> VelaVec;

// MATCH-ONLY: constructing the vector forces the vtable and its adjustor thunks into this unit.
void vela_use(void* p) { new (p) VelaVec(); }
