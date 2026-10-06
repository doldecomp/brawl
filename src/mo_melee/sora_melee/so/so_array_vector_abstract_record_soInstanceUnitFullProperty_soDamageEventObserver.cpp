#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soDamageEventObserver;

template soInstanceUnitFullProperty<soDamageEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soDamageEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soDamageEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soDamageEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soDamageEventObserver*> >::unshift(const soInstanceUnitFullProperty<soDamageEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soDamageEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soDamageEventObserver*> >::push(const soInstanceUnitFullProperty<soDamageEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soDamageEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soDamageEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soDamageEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soDamageEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soDamageEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soDamageEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soDamageEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soDamageEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soDamageEventObserver*> >::substitution(s32, s32);
