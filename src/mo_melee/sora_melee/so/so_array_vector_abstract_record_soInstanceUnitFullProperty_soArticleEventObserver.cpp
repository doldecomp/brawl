#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>

class soArticleEventObserver;

template soInstanceUnitFullProperty<soArticleEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soArticleEventObserver*> >::at(s32);
template const soInstanceUnitFullProperty<soArticleEventObserver*>& soArrayVectorAbstract<soInstanceUnitFullProperty<soArticleEventObserver*> >::at(s32) const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soArticleEventObserver*> >::unshift(const soInstanceUnitFullProperty<soArticleEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soArticleEventObserver*> >::shift();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soArticleEventObserver*> >::push(const soInstanceUnitFullProperty<soArticleEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soArticleEventObserver*> >::pop();
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soArticleEventObserver*> >::insert(s32, const soInstanceUnitFullProperty<soArticleEventObserver*>&);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soArticleEventObserver*> >::erase(s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soArticleEventObserver*> >::set(s32, const soInstanceUnitFullProperty<soArticleEventObserver*>&, s32);
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soArticleEventObserver*> >::clear();
template bool soArrayVectorAbstract<soInstanceUnitFullProperty<soArticleEventObserver*> >::isNull() const;
template void soArrayVectorAbstract<soInstanceUnitFullProperty<soArticleEventObserver*> >::substitution(s32, s32);
