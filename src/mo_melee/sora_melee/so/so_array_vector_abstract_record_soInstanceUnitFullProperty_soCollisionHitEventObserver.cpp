#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soCollisionHitEventObserver;

template soInstanceUnitFullProperty<soCollisionHitEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionHitEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soCollisionHitEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionHitEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionHitEventObserver*> >::unshift(const soInstanceUnitFullProperty<soCollisionHitEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionHitEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionHitEventObserver*> >::push(const soInstanceUnitFullProperty<soCollisionHitEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionHitEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionHitEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soCollisionHitEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionHitEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionHitEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soCollisionHitEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionHitEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionHitEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCollisionHitEventObserver*> >::substitution(s32, s32);
