#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soCollisionCatchEventObserver;

template soInstanceUnitFullProperty<soCollisionCatchEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionCatchEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soCollisionCatchEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionCatchEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionCatchEventObserver*> >::unshift(const soInstanceUnitFullProperty<soCollisionCatchEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionCatchEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionCatchEventObserver*> >::push(const soInstanceUnitFullProperty<soCollisionCatchEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionCatchEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionCatchEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soCollisionCatchEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionCatchEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionCatchEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soCollisionCatchEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionCatchEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionCatchEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionCatchEventObserver*> >::substitution(s32, s32);
