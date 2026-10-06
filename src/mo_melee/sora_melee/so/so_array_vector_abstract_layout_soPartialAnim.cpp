#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soPartialAnim.h>

template soPartialAnim& soArrayVectorAbstract<soPartialAnim>::at(s32);
template const soPartialAnim& soArrayVectorAbstract<soPartialAnim>::at(s32) const;
template void soArrayVectorAbstract<soPartialAnim>::unshift(const soPartialAnim&);
template void soArrayVectorAbstract<soPartialAnim>::shift();
template void soArrayVectorAbstract<soPartialAnim>::push(const soPartialAnim&);
template void soArrayVectorAbstract<soPartialAnim>::pop();
template void soArrayVectorAbstract<soPartialAnim>::insert(s32, const soPartialAnim&);
template void soArrayVectorAbstract<soPartialAnim>::erase(s32);
template void soArrayVectorAbstract<soPartialAnim>::set(s32, const soPartialAnim&, s32);
template void soArrayVectorAbstract<soPartialAnim>::clear();
template bool soArrayVectorAbstract<soPartialAnim>::isNull() const;
template void soArrayVectorAbstract<soPartialAnim>::substitution(s32, s32);
