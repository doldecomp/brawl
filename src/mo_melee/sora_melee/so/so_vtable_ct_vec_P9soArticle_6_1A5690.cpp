#pragma force_active off
#include <so/so_array.h>
class soArticle;
#include <new>

typedef soArticle* VelaElm;
typedef soArrayVector<VelaElm, 6> VelaVec;

// MATCH-ONLY: constructing the vector forces its vtable and special members into this unit.
#pragma dont_inline on
void vela_a(void* p) { new (p) VelaVec(); }
void vela_b(void* p) { new (p) VelaVec(1, 0); }
void vela_c(void* p, const VelaElm& e) { new (p) VelaVec(1, e, 0); }
void vela_del(VelaVec* p) { delete p; }
#pragma dont_inline reset
