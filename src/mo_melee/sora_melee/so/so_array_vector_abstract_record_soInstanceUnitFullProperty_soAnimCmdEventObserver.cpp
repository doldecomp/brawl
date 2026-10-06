#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soAnimCmdEventObserver;

template soInstanceUnitFullProperty<soAnimCmdEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soAnimCmdEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdEventObserver*> >::unshift(const soInstanceUnitFullProperty<soAnimCmdEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdEventObserver*> >::push(const soInstanceUnitFullProperty<soAnimCmdEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soAnimCmdEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soAnimCmdEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soAnimCmdEventObserver*> >::substitution(s32, s32);
