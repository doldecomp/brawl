#pragma force_active off
#include <so/so_array.h>
#include <so/collision/templates/so_collision_attack_part.h>
#include <new>

typedef soArrayVector<soCollisionAttackPart, 5> VelaVec;

// MATCH-ONLY: constructing the vector forces the vtable and its adjustor thunks into this unit.
void vela_use(void* p) { new (p) VelaVec(); }
