#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soGroundShapeImpl.h>

template soGroundShapeImpl& soArrayVectorAbstract<soGroundShapeImpl>::at(s32);
template const soGroundShapeImpl& soArrayVectorAbstract<soGroundShapeImpl>::at(s32) const;
template void soArrayVectorAbstract<soGroundShapeImpl>::unshift(const soGroundShapeImpl&);
template void soArrayVectorAbstract<soGroundShapeImpl>::shift();
template void soArrayVectorAbstract<soGroundShapeImpl>::push(const soGroundShapeImpl&);
template void soArrayVectorAbstract<soGroundShapeImpl>::pop();
template void soArrayVectorAbstract<soGroundShapeImpl>::insert(s32, const soGroundShapeImpl&);
template void soArrayVectorAbstract<soGroundShapeImpl>::erase(s32);
template void soArrayVectorAbstract<soGroundShapeImpl>::set(s32, const soGroundShapeImpl&, s32);
template void soArrayVectorAbstract<soGroundShapeImpl>::clear();
template bool soArrayVectorAbstract<soGroundShapeImpl>::isNull() const;
template void soArrayVectorAbstract<soGroundShapeImpl>::substitution(s32, s32);
