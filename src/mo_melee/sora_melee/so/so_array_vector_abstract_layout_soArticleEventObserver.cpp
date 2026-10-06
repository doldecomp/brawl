#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soArticleEventObserver.h>

template soArticleEventObserver& soArrayVectorAbstract<soArticleEventObserver>::at(s32);
template const soArticleEventObserver& soArrayVectorAbstract<soArticleEventObserver>::at(s32) const;
template void soArrayVectorAbstract<soArticleEventObserver>::unshift(const soArticleEventObserver&);
template void soArrayVectorAbstract<soArticleEventObserver>::shift();
template void soArrayVectorAbstract<soArticleEventObserver>::push(const soArticleEventObserver&);
template void soArrayVectorAbstract<soArticleEventObserver>::pop();
template void soArrayVectorAbstract<soArticleEventObserver>::insert(s32, const soArticleEventObserver&);
template void soArrayVectorAbstract<soArticleEventObserver>::erase(s32);
template void soArrayVectorAbstract<soArticleEventObserver>::set(s32, const soArticleEventObserver&, s32);
template void soArrayVectorAbstract<soArticleEventObserver>::clear();
template bool soArrayVectorAbstract<soArticleEventObserver>::isNull() const;
template void soArrayVectorAbstract<soArticleEventObserver>::substitution(s32, s32);
