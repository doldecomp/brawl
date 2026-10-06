#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soPhysicsIKHandle.h>

template soPhysicsIKHandle& soArrayVectorAbstract<soPhysicsIKHandle>::at(s32);
template const soPhysicsIKHandle& soArrayVectorAbstract<soPhysicsIKHandle>::at(s32) const;
template void soArrayVectorAbstract<soPhysicsIKHandle>::unshift(const soPhysicsIKHandle&);
template void soArrayVectorAbstract<soPhysicsIKHandle>::shift();
template void soArrayVectorAbstract<soPhysicsIKHandle>::push(const soPhysicsIKHandle&);
template void soArrayVectorAbstract<soPhysicsIKHandle>::pop();
template void soArrayVectorAbstract<soPhysicsIKHandle>::insert(s32, const soPhysicsIKHandle&);
template void soArrayVectorAbstract<soPhysicsIKHandle>::erase(s32);
template void soArrayVectorAbstract<soPhysicsIKHandle>::set(s32, const soPhysicsIKHandle&, s32);
template void soArrayVectorAbstract<soPhysicsIKHandle>::clear();
template bool soArrayVectorAbstract<soPhysicsIKHandle>::isNull() const;
template void soArrayVectorAbstract<soPhysicsIKHandle>::substitution(s32, s32);
