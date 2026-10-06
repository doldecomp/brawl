#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_area_instance.h>


template soAreaInstance& soArrayVectorAbstract<soAreaInstance>::at(s32);
template const soAreaInstance& soArrayVectorAbstract<soAreaInstance>::at(s32) const;
template void soArrayVectorAbstract<soAreaInstance>::unshift(const soAreaInstance&);
template void soArrayVectorAbstract<soAreaInstance>::shift();
template void soArrayVectorAbstract<soAreaInstance>::push(const soAreaInstance&);
template void soArrayVectorAbstract<soAreaInstance>::pop();
template void soArrayVectorAbstract<soAreaInstance>::insert(s32, const soAreaInstance&);
template void soArrayVectorAbstract<soAreaInstance>::erase(s32);
template void soArrayVectorAbstract<soAreaInstance>::set(s32, const soAreaInstance&, s32);
template void soArrayVectorAbstract<soAreaInstance>::clear();
template bool soArrayVectorAbstract<soAreaInstance>::isNull() const;
template void soArrayVectorAbstract<soAreaInstance>::substitution(s32, s32);
