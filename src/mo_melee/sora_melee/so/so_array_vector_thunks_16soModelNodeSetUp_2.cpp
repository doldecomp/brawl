#pragma force_active off
#include <so/so_array.h>
#include <so/templates/so_model_node_set_up.h>
#include <new>

typedef soArrayVector<soModelNodeSetUp, 2> VelaVec;

// MATCH-ONLY: constructing the vector forces the vtable and its adjustor thunks into this unit.
void vela_use(void* p) { new (p) VelaVec(); }
