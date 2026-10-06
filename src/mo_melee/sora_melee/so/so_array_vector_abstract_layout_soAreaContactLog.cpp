#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soAreaContactLog.h>

template soAreaContactLog& soArrayVectorAbstract<soAreaContactLog>::at(s32);
template const soAreaContactLog& soArrayVectorAbstract<soAreaContactLog>::at(s32) const;
template void soArrayVectorAbstract<soAreaContactLog>::unshift(const soAreaContactLog&);
template void soArrayVectorAbstract<soAreaContactLog>::shift();
template void soArrayVectorAbstract<soAreaContactLog>::push(const soAreaContactLog&);
template void soArrayVectorAbstract<soAreaContactLog>::pop();
template void soArrayVectorAbstract<soAreaContactLog>::insert(s32, const soAreaContactLog&);
template void soArrayVectorAbstract<soAreaContactLog>::erase(s32);
template void soArrayVectorAbstract<soAreaContactLog>::set(s32, const soAreaContactLog&, s32);
template void soArrayVectorAbstract<soAreaContactLog>::clear();
template bool soArrayVectorAbstract<soAreaContactLog>::isNull() const;
template void soArrayVectorAbstract<soAreaContactLog>::substitution(s32, s32);
