#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soMotionEventObserver;

template soInstanceUnitFullProperty<soMotionEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soMotionEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soMotionEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soMotionEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soMotionEventObserver*> >::unshift(const soInstanceUnitFullProperty<soMotionEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soMotionEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soMotionEventObserver*> >::push(const soInstanceUnitFullProperty<soMotionEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soMotionEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soMotionEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soMotionEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soMotionEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soMotionEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soMotionEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soMotionEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soMotionEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soMotionEventObserver*> >::substitution(s32, s32);
