#pragma force_active off
#include <so/posture/so_posture_module_impl.h>
#include <new>

typedef soArrayVector<soInterpolation<Vec3f>, 26> VelaVec;

// MATCH-ONLY: constructing the vector forces the vtable and its adjustor thunks into this unit.
void vela_use(void* p) { new (p) VelaVec(); }
