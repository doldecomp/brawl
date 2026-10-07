#pragma force_active off
#include <so/so_array.h>
#include <revolution/gx.h>
#include <so/collision/templates/so_collision_hit_part.h>
#include <new>

typedef soArrayVector<soCollisionHitPart, 11> VelaVec;

// MATCH-ONLY: constructing the vector forces the vtable and its adjustor thunks into this unit.
void vela_use(void* p) { new (p) VelaVec(); }
