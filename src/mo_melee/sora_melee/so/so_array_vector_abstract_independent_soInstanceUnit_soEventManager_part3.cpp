#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soEventManager;

template void soArrayVectorAbstract<soInstanceUnit<soEventManager*> >::insert(s32, const soInstanceUnit<soEventManager*>&);
template void soArrayVectorAbstract<soInstanceUnit<soEventManager*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnit<soEventManager*> >::set(s32, const soInstanceUnit<soEventManager*>&, s32);
template void soArrayVectorAbstract<soInstanceUnit<soEventManager*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnit<soEventManager*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnit<soEventManager*> >::substitution(s32, s32);
