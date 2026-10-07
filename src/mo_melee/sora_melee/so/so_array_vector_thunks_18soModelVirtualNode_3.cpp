#pragma force_active off
#include <so/so_array.h>
#include <so/model/so_model_virtual_node.h>
#include <new>

typedef soArrayVector<soModelVirtualNode, 3> VelaVec;

// MATCH-ONLY: constructing the vector forces the vtable and its adjustor thunks into this unit.
void vela_use(void* p) { new (p) VelaVec(); }
