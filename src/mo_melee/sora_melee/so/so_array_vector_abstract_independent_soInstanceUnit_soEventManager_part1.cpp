#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soEventManager;

template soInstanceUnit<soEventManager*>& soArrayVectorAbstract<soInstanceUnit<soEventManager*> >::at(s32);
template const soInstanceUnit<soEventManager*>& soArrayVectorAbstract<soInstanceUnit<soEventManager*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnit<soEventManager*> >::unshift(const soInstanceUnit<soEventManager*>&);
