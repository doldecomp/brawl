#pragma force_active on
#include <so/so_array.h>

class BaseItem;

template BaseItem*& soArrayVectorAbstract<BaseItem*>::at(s32);
template BaseItem* const& soArrayVectorAbstract<BaseItem*>::at(s32) const;
template void soArrayVectorAbstract<BaseItem*>::unshift(BaseItem* const&);
template void soArrayVectorAbstract<BaseItem*>::shift();
template void soArrayVectorAbstract<BaseItem*>::push(BaseItem* const&);
template void soArrayVectorAbstract<BaseItem*>::pop();
template void soArrayVectorAbstract<BaseItem*>::insert(s32, BaseItem* const&);
template void soArrayVectorAbstract<BaseItem*>::erase(s32);
template void soArrayVectorAbstract<BaseItem*>::set(s32, BaseItem* const&, s32);
template void soArrayVectorAbstract<BaseItem*>::clear();
template bool soArrayVectorAbstract<BaseItem*>::isNull() const;
template void soArrayVectorAbstract<BaseItem*>::substitution(s32, s32);
