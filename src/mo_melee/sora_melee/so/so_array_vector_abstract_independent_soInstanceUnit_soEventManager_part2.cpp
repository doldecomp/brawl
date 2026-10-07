#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soEventManager;

template void soArrayVectorAbstract<soInstanceUnit<soEventManager*> >::push(const soInstanceUnit<soEventManager*>&);
