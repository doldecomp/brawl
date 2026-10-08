#pragma force_active off
#include <so/so_array.h>
#include <so/model/so_model_virtual_node.h>
#include <new>

typedef soModelVirtualNode VelaElm;
typedef soArrayVector<VelaElm, 1> VelaVec;

// MATCH-ONLY: constructing/deleting the vector forces its base-class members into this unit.
#pragma dont_inline on
void vela_a(void* p) { new (p) VelaVec(); }
void vela_del(VelaVec* p) { delete p; }
#pragma dont_inline reset
