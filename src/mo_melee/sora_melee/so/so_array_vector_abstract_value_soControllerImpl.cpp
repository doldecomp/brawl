#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_controller_impl.h>


template soControllerImpl& soArrayVectorAbstract<soControllerImpl>::at(s32);
template const soControllerImpl& soArrayVectorAbstract<soControllerImpl>::at(s32) const;
template void soArrayVectorAbstract<soControllerImpl>::unshift(const soControllerImpl&);
template void soArrayVectorAbstract<soControllerImpl>::shift();
template void soArrayVectorAbstract<soControllerImpl>::push(const soControllerImpl&);
template void soArrayVectorAbstract<soControllerImpl>::pop();
template void soArrayVectorAbstract<soControllerImpl>::insert(s32, const soControllerImpl&);
template void soArrayVectorAbstract<soControllerImpl>::erase(s32);
template void soArrayVectorAbstract<soControllerImpl>::set(s32, const soControllerImpl&, s32);
template void soArrayVectorAbstract<soControllerImpl>::clear();
template bool soArrayVectorAbstract<soControllerImpl>::isNull() const;
template void soArrayVectorAbstract<soControllerImpl>::substitution(s32, s32);
