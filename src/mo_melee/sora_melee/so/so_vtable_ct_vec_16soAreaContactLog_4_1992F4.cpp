#pragma force_active off
#include <so/so_array.h>
#include <so/templates/so_array_value_soAreaContactLog.h>
#include <new>

typedef soAreaContactLog VelaElm;
typedef soArrayVector<VelaElm, 4> VelaVec;

// MATCH-ONLY: constructing the vector forces its vtable and special members into this unit.
#pragma dont_inline on
void vela_a(void* p) { new (p) VelaVec(); }
void vela_b(void* p) { new (p) VelaVec(1, 0); }
void vela_c(void* p, const VelaElm& e) { new (p) VelaVec(1, e, 0); }
void vela_del(VelaVec* p) { delete p; }
#pragma dont_inline reset
