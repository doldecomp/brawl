#pragma force_active off
#include <so/so_array.h>
#include <ef/ef_screen_handle.h>
#include <new>

typedef soArrayVector<efScreenHandle, 2> VelaVec;

// MATCH-ONLY: constructing the vector forces the vtable and its adjustor thunks into this unit.
void vela_use(void* p) { new (p) VelaVec(); }
