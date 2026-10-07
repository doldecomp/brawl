#pragma force_active on
#include <so/so_array.h>
class soKineticEnergy;

template s32 soArrayVector<soKineticEnergy**, 24>::size() const;
template s32 soArrayVector<soKineticEnergy**, 24>::getTopIndex() const;
template void soArrayVector<soKineticEnergy**, 24>::setTopIndex(s32);
template s32 soArrayVector<soKineticEnergy**, 24>::getLastIndex() const;
template void soArrayVector<soKineticEnergy**, 24>::setLastIndex(s32);
template soKineticEnergy**& soArrayVector<soKineticEnergy**, 24>::getArrayValueConst(s32);
template void soArrayVector<soKineticEnergy**, 24>::onFull();
template void soArrayVector<soKineticEnergy**, 24>::offFull();
template bool soArrayVector<soKineticEnergy**, 24>::isFull() const;
template s32 soArrayVector<soKineticEnergy**, 24>::capacity() const;
template soKineticEnergy**& soArrayVector<soKineticEnergy**, 24>::atFastAbstractSub(s32) const;
template void soArrayVector<soKineticEnergy**, 24>::setSize(s32);
