#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soEventUnit;

template soInstanceUnit<soEventUnit*>& soArrayVectorAbstract<soInstanceUnit<soEventUnit*> >::at(s32);
template const soInstanceUnit<soEventUnit*>& soArrayVectorAbstract<soInstanceUnit<soEventUnit*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnit<soEventUnit*> >::unshift(const soInstanceUnit<soEventUnit*>&);
template void soArrayVectorAbstract<soInstanceUnit<soEventUnit*> >::shift();
template void soArrayVectorAbstract<soInstanceUnit<soEventUnit*> >::push(const soInstanceUnit<soEventUnit*>&);
template void soArrayVectorAbstract<soInstanceUnit<soEventUnit*> >::pop();
template void soArrayVectorAbstract<soInstanceUnit<soEventUnit*> >::insert(s32, const soInstanceUnit<soEventUnit*>&);
template void soArrayVectorAbstract<soInstanceUnit<soEventUnit*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnit<soEventUnit*> >::set(s32, const soInstanceUnit<soEventUnit*>&, s32);
template void soArrayVectorAbstract<soInstanceUnit<soEventUnit*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnit<soEventUnit*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnit<soEventUnit*> >::substitution(s32, s32);
