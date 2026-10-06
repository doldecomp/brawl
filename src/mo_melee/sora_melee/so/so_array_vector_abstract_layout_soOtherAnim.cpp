#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soOtherAnim.h>

template soOtherAnim& soArrayVectorAbstract<soOtherAnim>::at(s32);
template const soOtherAnim& soArrayVectorAbstract<soOtherAnim>::at(s32) const;
template void soArrayVectorAbstract<soOtherAnim>::unshift(const soOtherAnim&);
template void soArrayVectorAbstract<soOtherAnim>::shift();
template void soArrayVectorAbstract<soOtherAnim>::push(const soOtherAnim&);
template void soArrayVectorAbstract<soOtherAnim>::pop();
template void soArrayVectorAbstract<soOtherAnim>::insert(s32, const soOtherAnim&);
template void soArrayVectorAbstract<soOtherAnim>::erase(s32);
template void soArrayVectorAbstract<soOtherAnim>::set(s32, const soOtherAnim&, s32);
template void soArrayVectorAbstract<soOtherAnim>::clear();
template bool soArrayVectorAbstract<soOtherAnim>::isNull() const;
template void soArrayVectorAbstract<soOtherAnim>::substitution(s32, s32);
