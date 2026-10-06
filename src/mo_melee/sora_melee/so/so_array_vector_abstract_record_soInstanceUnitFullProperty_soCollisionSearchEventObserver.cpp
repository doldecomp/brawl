#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soCollisionSearchEventObserver;

template soInstanceUnitFullProperty<soCollisionSearchEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionSearchEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soCollisionSearchEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionSearchEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionSearchEventObserver*> >::unshift(const soInstanceUnitFullProperty<soCollisionSearchEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionSearchEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionSearchEventObserver*> >::push(const soInstanceUnitFullProperty<soCollisionSearchEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionSearchEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionSearchEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soCollisionSearchEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionSearchEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionSearchEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soCollisionSearchEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionSearchEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionSearchEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionSearchEventObserver*> >::substitution(s32, s32);
