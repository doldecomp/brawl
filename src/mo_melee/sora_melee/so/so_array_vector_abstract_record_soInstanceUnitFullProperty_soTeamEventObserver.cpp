#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soTeamEventObserver;

template soInstanceUnitFullProperty<soTeamEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soTeamEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soTeamEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soTeamEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTeamEventObserver*> >::unshift(const soInstanceUnitFullProperty<soTeamEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTeamEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTeamEventObserver*> >::push(const soInstanceUnitFullProperty<soTeamEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTeamEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTeamEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soTeamEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTeamEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTeamEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soTeamEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTeamEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soTeamEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soTeamEventObserver*> >::substitution(s32, s32);
