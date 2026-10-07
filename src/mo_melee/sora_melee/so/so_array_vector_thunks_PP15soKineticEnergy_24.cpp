#pragma force_active off
#include <so/so_array.h>
class soKineticEnergy;
#include <new>

typedef soArrayVector<soKineticEnergy**, 24> VelaVec;

// MATCH-ONLY: constructing the vector forces the vtable and its adjustor thunks into this unit.
void vela_use(void* p) { new (p) VelaVec(); }
