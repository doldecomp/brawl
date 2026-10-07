#pragma force_active off
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
#include <so/templates/so_array_value_soTransitionTerm.h>
#include <new>

typedef soArrayVector<soInstanceUnitFullProperty<soTransitionTerm>, 8> Vec;

// MATCH-ONLY: constructing the vector forces the vtable and its adjustor thunks into this unit.
void vela_use(void* p) { new (p) Vec(); }
