#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soStatusEventObserver;

template soInstanceUnitFullProperty<soStatusEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soStatusEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soStatusEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soStatusEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soStatusEventObserver*> >::unshift(const soInstanceUnitFullProperty<soStatusEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soStatusEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soStatusEventObserver*> >::push(const soInstanceUnitFullProperty<soStatusEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soStatusEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soStatusEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soStatusEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soStatusEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soStatusEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soStatusEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soStatusEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soStatusEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soStatusEventObserver*> >::substitution(s32, s32);
