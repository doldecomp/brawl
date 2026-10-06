#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soItemManageEventObserver;

template soInstanceUnitFullProperty<soItemManageEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soItemManageEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soItemManageEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soItemManageEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soItemManageEventObserver*> >::unshift(const soInstanceUnitFullProperty<soItemManageEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soItemManageEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soItemManageEventObserver*> >::push(const soInstanceUnitFullProperty<soItemManageEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soItemManageEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soItemManageEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soItemManageEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soItemManageEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soItemManageEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soItemManageEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soItemManageEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soItemManageEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soItemManageEventObserver*> >::substitution(s32, s32);
