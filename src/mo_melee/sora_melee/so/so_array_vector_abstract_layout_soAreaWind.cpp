#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soAreaWind.h>

template soAreaWind& soArrayVectorAbstract<soAreaWind>::at(s32);
template const soAreaWind& soArrayVectorAbstract<soAreaWind>::at(s32) const;
template void soArrayVectorAbstract<soAreaWind>::unshift(const soAreaWind&);
template void soArrayVectorAbstract<soAreaWind>::shift();
template void soArrayVectorAbstract<soAreaWind>::push(const soAreaWind&);
template void soArrayVectorAbstract<soAreaWind>::pop();
template void soArrayVectorAbstract<soAreaWind>::insert(s32, const soAreaWind&);
template void soArrayVectorAbstract<soAreaWind>::erase(s32);
template void soArrayVectorAbstract<soAreaWind>::set(s32, const soAreaWind&, s32);
template void soArrayVectorAbstract<soAreaWind>::clear();
template bool soArrayVectorAbstract<soAreaWind>::isNull() const;
template void soArrayVectorAbstract<soAreaWind>::substitution(s32, s32);
