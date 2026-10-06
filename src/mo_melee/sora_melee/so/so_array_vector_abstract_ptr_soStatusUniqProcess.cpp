#pragma force_active on
#include <so/so_array.h>

class soStatusUniqProcess;

template soStatusUniqProcess*& soArrayVectorAbstract<soStatusUniqProcess*>::at(s32);
template soStatusUniqProcess* const& soArrayVectorAbstract<soStatusUniqProcess*>::at(s32) const;
template void soArrayVectorAbstract<soStatusUniqProcess*>::unshift(soStatusUniqProcess* const&);
template void soArrayVectorAbstract<soStatusUniqProcess*>::shift();
template void soArrayVectorAbstract<soStatusUniqProcess*>::push(soStatusUniqProcess* const&);
template void soArrayVectorAbstract<soStatusUniqProcess*>::pop();
template void soArrayVectorAbstract<soStatusUniqProcess*>::insert(s32, soStatusUniqProcess* const&);
template void soArrayVectorAbstract<soStatusUniqProcess*>::erase(s32);
template void soArrayVectorAbstract<soStatusUniqProcess*>::set(s32, soStatusUniqProcess* const&, s32);
template void soArrayVectorAbstract<soStatusUniqProcess*>::clear();
template bool soArrayVectorAbstract<soStatusUniqProcess*>::isNull() const;
template void soArrayVectorAbstract<soStatusUniqProcess*>::substitution(s32, s32);
