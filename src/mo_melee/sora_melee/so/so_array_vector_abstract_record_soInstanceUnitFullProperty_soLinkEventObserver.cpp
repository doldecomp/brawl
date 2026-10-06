#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soLinkEventObserver;

template soInstanceUnitFullProperty<soLinkEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soLinkEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soLinkEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soLinkEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLinkEventObserver*> >::unshift(const soInstanceUnitFullProperty<soLinkEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLinkEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLinkEventObserver*> >::push(const soInstanceUnitFullProperty<soLinkEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLinkEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLinkEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soLinkEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLinkEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLinkEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soLinkEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLinkEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soLinkEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soLinkEventObserver*> >::substitution(s32, s32);
