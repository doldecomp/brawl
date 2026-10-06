#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soGimmickEventObserver;

template soInstanceUnitFullProperty<soGimmickEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soGimmickEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soGimmickEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soGimmickEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soGimmickEventObserver*> >::unshift(const soInstanceUnitFullProperty<soGimmickEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soGimmickEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soGimmickEventObserver*> >::push(const soInstanceUnitFullProperty<soGimmickEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soGimmickEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soGimmickEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soGimmickEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soGimmickEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soGimmickEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soGimmickEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soGimmickEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soGimmickEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soGimmickEventObserver*> >::substitution(s32, s32);
