#pragma force_active off
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
class soTurnEventObserver;
#include <new>

typedef soInstanceUnitFullProperty<soTurnEventObserver*> VelaElm;
typedef soArrayVector<VelaElm, 2> VelaVec;

// MATCH-ONLY: constructing/deleting the vector forces its base-class members into this unit.
#pragma dont_inline on
void vela_a(void* p) { new (p) VelaVec(); }
void vela_del(VelaVec* p) { delete p; }
#pragma dont_inline reset
