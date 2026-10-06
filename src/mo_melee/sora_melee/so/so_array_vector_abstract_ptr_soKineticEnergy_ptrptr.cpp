#pragma force_active on
#include <so/so_array.h>

class soKineticEnergy;

template soKineticEnergy**& soArrayVectorAbstract<soKineticEnergy**>::at(s32);
template soKineticEnergy** const& soArrayVectorAbstract<soKineticEnergy**>::at(s32) const;
template void soArrayVectorAbstract<soKineticEnergy**>::unshift(soKineticEnergy** const&);
template void soArrayVectorAbstract<soKineticEnergy**>::shift();
template void soArrayVectorAbstract<soKineticEnergy**>::push(soKineticEnergy** const&);
template void soArrayVectorAbstract<soKineticEnergy**>::pop();
template void soArrayVectorAbstract<soKineticEnergy**>::insert(s32, soKineticEnergy** const&);
template void soArrayVectorAbstract<soKineticEnergy**>::erase(s32);
template void soArrayVectorAbstract<soKineticEnergy**>::set(s32, soKineticEnergy** const&, s32);
template void soArrayVectorAbstract<soKineticEnergy**>::clear();
template bool soArrayVectorAbstract<soKineticEnergy**>::isNull() const;
template void soArrayVectorAbstract<soKineticEnergy**>::substitution(s32, s32);
