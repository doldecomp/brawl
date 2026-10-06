#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_emAIInfo.h>

template emAIInfo& soArrayVectorAbstract<emAIInfo>::at(s32);
template const emAIInfo& soArrayVectorAbstract<emAIInfo>::at(s32) const;
template void soArrayVectorAbstract<emAIInfo>::unshift(const emAIInfo&);
template void soArrayVectorAbstract<emAIInfo>::shift();
template void soArrayVectorAbstract<emAIInfo>::push(const emAIInfo&);
template void soArrayVectorAbstract<emAIInfo>::pop();
template void soArrayVectorAbstract<emAIInfo>::insert(s32, const emAIInfo&);
template void soArrayVectorAbstract<emAIInfo>::erase(s32);
template void soArrayVectorAbstract<emAIInfo>::set(s32, const emAIInfo&, s32);
template void soArrayVectorAbstract<emAIInfo>::clear();
template bool soArrayVectorAbstract<emAIInfo>::isNull() const;
template void soArrayVectorAbstract<emAIInfo>::substitution(s32, s32);
