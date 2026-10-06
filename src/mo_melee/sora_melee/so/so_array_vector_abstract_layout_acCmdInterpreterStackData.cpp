#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_acCmdInterpreterStackData.h>

template acCmdInterpreterStackData& soArrayVectorAbstract<acCmdInterpreterStackData>::at(s32);
template const acCmdInterpreterStackData& soArrayVectorAbstract<acCmdInterpreterStackData>::at(s32) const;
template void soArrayVectorAbstract<acCmdInterpreterStackData>::unshift(const acCmdInterpreterStackData&);
template void soArrayVectorAbstract<acCmdInterpreterStackData>::shift();
template void soArrayVectorAbstract<acCmdInterpreterStackData>::push(const acCmdInterpreterStackData&);
template void soArrayVectorAbstract<acCmdInterpreterStackData>::pop();
template void soArrayVectorAbstract<acCmdInterpreterStackData>::insert(s32, const acCmdInterpreterStackData&);
template void soArrayVectorAbstract<acCmdInterpreterStackData>::erase(s32);
template void soArrayVectorAbstract<acCmdInterpreterStackData>::set(s32, const acCmdInterpreterStackData&, s32);
template void soArrayVectorAbstract<acCmdInterpreterStackData>::clear();
template bool soArrayVectorAbstract<acCmdInterpreterStackData>::isNull() const;
template void soArrayVectorAbstract<acCmdInterpreterStackData>::substitution(s32, s32);
