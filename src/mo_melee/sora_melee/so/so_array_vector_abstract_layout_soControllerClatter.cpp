#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soControllerClatter.h>

template soControllerClatter& soArrayVectorAbstract<soControllerClatter>::at(s32);
template const soControllerClatter& soArrayVectorAbstract<soControllerClatter>::at(s32) const;
template void soArrayVectorAbstract<soControllerClatter>::unshift(const soControllerClatter&);
template void soArrayVectorAbstract<soControllerClatter>::shift();
template void soArrayVectorAbstract<soControllerClatter>::push(const soControllerClatter&);
template void soArrayVectorAbstract<soControllerClatter>::pop();
template void soArrayVectorAbstract<soControllerClatter>::insert(s32, const soControllerClatter&);
template void soArrayVectorAbstract<soControllerClatter>::erase(s32);
template void soArrayVectorAbstract<soControllerClatter>::set(s32, const soControllerClatter&, s32);
template void soArrayVectorAbstract<soControllerClatter>::clear();
template bool soArrayVectorAbstract<soControllerClatter>::isNull() const;
template void soArrayVectorAbstract<soControllerClatter>::substitution(s32, s32);
