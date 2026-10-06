#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class ftEntryEventObserver;

template soInstanceUnitFullProperty<ftEntryEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<ftEntryEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<ftEntryEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<ftEntryEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftEntryEventObserver*> >::unshift(const soInstanceUnitFullProperty<ftEntryEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftEntryEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftEntryEventObserver*> >::push(const soInstanceUnitFullProperty<ftEntryEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftEntryEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftEntryEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<ftEntryEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftEntryEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftEntryEventObserver*> >::set(s32, const soInstanceUnitFullProperty<ftEntryEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftEntryEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<ftEntryEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<ftEntryEventObserver*> >::substitution(s32, s32);
