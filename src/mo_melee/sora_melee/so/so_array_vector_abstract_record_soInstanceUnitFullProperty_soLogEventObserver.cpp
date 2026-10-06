#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soLogEventObserver;

template soInstanceUnitFullProperty<soLogEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soLogEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soLogEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soLogEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLogEventObserver*> >::unshift(const soInstanceUnitFullProperty<soLogEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLogEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLogEventObserver*> >::push(const soInstanceUnitFullProperty<soLogEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLogEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLogEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soLogEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLogEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLogEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soLogEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLogEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soLogEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLogEventObserver*> >::substitution(s32, s32);
