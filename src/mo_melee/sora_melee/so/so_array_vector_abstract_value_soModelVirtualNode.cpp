#pragma force_active on
#include <so/so_array.h>
#include <so/model/so_model_virtual_node.h>


template soModelVirtualNode& soArrayVectorAbstract<soModelVirtualNode>::at(s32);
template const soModelVirtualNode& soArrayVectorAbstract<soModelVirtualNode>::at(s32) const;
template void soArrayVectorAbstract<soModelVirtualNode>::unshift(const soModelVirtualNode&);
template void soArrayVectorAbstract<soModelVirtualNode>::shift();
template void soArrayVectorAbstract<soModelVirtualNode>::push(const soModelVirtualNode&);
template void soArrayVectorAbstract<soModelVirtualNode>::pop();
template void soArrayVectorAbstract<soModelVirtualNode>::insert(s32, const soModelVirtualNode&);
template void soArrayVectorAbstract<soModelVirtualNode>::erase(s32);
template void soArrayVectorAbstract<soModelVirtualNode>::set(s32, const soModelVirtualNode&, s32);
template void soArrayVectorAbstract<soModelVirtualNode>::clear();
template bool soArrayVectorAbstract<soModelVirtualNode>::isNull() const;
template void soArrayVectorAbstract<soModelVirtualNode>::substitution(s32, s32);
