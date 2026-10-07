#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soArticleEventObserver.h>

template s32 soArrayVector<soArticleEventObserver, 1>::getTopIndex() const;
template void soArrayVector<soArticleEventObserver, 1>::setTopIndex(s32);
template s32 soArrayVector<soArticleEventObserver, 1>::getLastIndex() const;
template void soArrayVector<soArticleEventObserver, 1>::setLastIndex(s32);
template soArticleEventObserver& soArrayVector<soArticleEventObserver, 1>::getArrayValueConst(s32);
template void soArrayVector<soArticleEventObserver, 1>::onFull();
template void soArrayVector<soArticleEventObserver, 1>::offFull();
template bool soArrayVector<soArticleEventObserver, 1>::isFull() const;
template s32 soArrayVector<soArticleEventObserver, 1>::capacity() const;
template s32 soArrayVector<soArticleEventObserver, 1>::size() const;
template void soArrayVector<soArticleEventObserver, 1>::setSize(s32);
