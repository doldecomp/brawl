#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class ftOutsideEventObserver;

template soInstanceUnitFullProperty<ftOutsideEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<ftOutsideEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<ftOutsideEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<ftOutsideEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftOutsideEventObserver*> >::unshift(const soInstanceUnitFullProperty<ftOutsideEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftOutsideEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftOutsideEventObserver*> >::push(const soInstanceUnitFullProperty<ftOutsideEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftOutsideEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftOutsideEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<ftOutsideEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftOutsideEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftOutsideEventObserver*> >::set(s32, const soInstanceUnitFullProperty<ftOutsideEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftOutsideEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<ftOutsideEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftOutsideEventObserver*> >::substitution(s32, s32);
