#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_wnemProcFncObj.h>

template wnemProcFncObj& soArrayVectorAbstract<wnemProcFncObj>::at(s32);
template const wnemProcFncObj& soArrayVectorAbstract<wnemProcFncObj>::at(s32) const;
template void soArrayVectorAbstract<wnemProcFncObj>::unshift(const wnemProcFncObj&);
template void soArrayVectorAbstract<wnemProcFncObj>::shift();
template void soArrayVectorAbstract<wnemProcFncObj>::push(const wnemProcFncObj&);
template void soArrayVectorAbstract<wnemProcFncObj>::pop();
template void soArrayVectorAbstract<wnemProcFncObj>::insert(s32, const wnemProcFncObj&);
template void soArrayVectorAbstract<wnemProcFncObj>::erase(s32);
template void soArrayVectorAbstract<wnemProcFncObj>::set(s32, const wnemProcFncObj&, s32);
template void soArrayVectorAbstract<wnemProcFncObj>::clear();
template bool soArrayVectorAbstract<wnemProcFncObj>::isNull() const;
template void soArrayVectorAbstract<wnemProcFncObj>::substitution(s32, s32);
