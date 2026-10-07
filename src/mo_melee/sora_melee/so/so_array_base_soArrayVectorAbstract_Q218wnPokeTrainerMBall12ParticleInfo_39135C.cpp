#pragma force_active off
#include <so/so_array.h>
#include <so/templates/so_array_value_wnPokeTrainerMBall_ParticleInfo.h>
#include <new>

typedef wnPokeTrainerMBall::ParticleInfo VelaElm;
typedef soArrayVector<VelaElm, 2> VelaVec;

// MATCH-ONLY: constructing/deleting the vector forces its base-class members into this unit.
#pragma dont_inline on
void vela_a(void* p) { new (p) VelaVec(); }
void vela_del(VelaVec* p) { delete p; }
#pragma dont_inline reset
