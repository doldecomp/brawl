#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_model_node_set_up.h>


template soModelNodeSetUp& soArrayVectorAbstract<soModelNodeSetUp>::at(s32);
template const soModelNodeSetUp& soArrayVectorAbstract<soModelNodeSetUp>::at(s32) const;
template void soArrayVectorAbstract<soModelNodeSetUp>::unshift(const soModelNodeSetUp&);
template void soArrayVectorAbstract<soModelNodeSetUp>::shift();
template void soArrayVectorAbstract<soModelNodeSetUp>::push(const soModelNodeSetUp&);
template void soArrayVectorAbstract<soModelNodeSetUp>::pop();
template void soArrayVectorAbstract<soModelNodeSetUp>::insert(s32, const soModelNodeSetUp&);
template void soArrayVectorAbstract<soModelNodeSetUp>::erase(s32);
template void soArrayVectorAbstract<soModelNodeSetUp>::set(s32, const soModelNodeSetUp&, s32);
template void soArrayVectorAbstract<soModelNodeSetUp>::clear();
template bool soArrayVectorAbstract<soModelNodeSetUp>::isNull() const;
template void soArrayVectorAbstract<soModelNodeSetUp>::substitution(s32, s32);
