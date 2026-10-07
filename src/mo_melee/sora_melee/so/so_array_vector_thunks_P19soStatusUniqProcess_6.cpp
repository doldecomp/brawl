#pragma force_active off
#include <so/so_array.h>
class soStatusUniqProcess;
#include <new>

typedef soArrayVector<soStatusUniqProcess*, 6> VelaVec;

// MATCH-ONLY: constructing the vector forces the vtable and its adjustor thunks into this unit.
void vela_use(void* p) { new (p) VelaVec(); }
