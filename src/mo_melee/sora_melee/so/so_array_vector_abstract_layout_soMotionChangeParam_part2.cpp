#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soMotionChangeParam.h>

template const soMotionChangeParam& soArrayVectorAbstract<soMotionChangeParam>::at(s32) const;
template void soArrayVectorAbstract<soMotionChangeParam>::unshift(const soMotionChangeParam&);
template void soArrayVectorAbstract<soMotionChangeParam>::pop();
template void soArrayVectorAbstract<soMotionChangeParam>::insert(s32, const soMotionChangeParam&);
template void soArrayVectorAbstract<soMotionChangeParam>::erase(s32);
