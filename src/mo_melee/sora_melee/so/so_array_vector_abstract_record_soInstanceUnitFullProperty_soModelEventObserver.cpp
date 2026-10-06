#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soModelEventObserver;

template soInstanceUnitFullProperty<soModelEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soModelEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soModelEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soModelEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soModelEventObserver*> >::unshift(const soInstanceUnitFullProperty<soModelEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soModelEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soModelEventObserver*> >::push(const soInstanceUnitFullProperty<soModelEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soModelEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soModelEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soModelEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soModelEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soModelEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soModelEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soModelEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soModelEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soModelEventObserver*> >::substitution(s32, s32);
