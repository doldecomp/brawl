#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soCaptureEventObserver;

template soInstanceUnitFullProperty<soCaptureEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soCaptureEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soCaptureEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soCaptureEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCaptureEventObserver*> >::unshift(const soInstanceUnitFullProperty<soCaptureEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCaptureEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCaptureEventObserver*> >::push(const soInstanceUnitFullProperty<soCaptureEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCaptureEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCaptureEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soCaptureEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCaptureEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCaptureEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soCaptureEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCaptureEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soCaptureEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soCaptureEventObserver*> >::substitution(s32, s32);
