#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soArticleEventObserver.h>

template s32 soArrayVector<soArticleEventObserver, 8>::getTopIndex() const;
template void soArrayVector<soArticleEventObserver, 8>::setTopIndex(s32);
template s32 soArrayVector<soArticleEventObserver, 8>::getLastIndex() const;
template void soArrayVector<soArticleEventObserver, 8>::setLastIndex(s32);
template soArticleEventObserver& soArrayVector<soArticleEventObserver, 8>::getArrayValueConst(s32);
template void soArrayVector<soArticleEventObserver, 8>::onFull();
template void soArrayVector<soArticleEventObserver, 8>::offFull();
template bool soArrayVector<soArticleEventObserver, 8>::isFull() const;
template s32 soArrayVector<soArticleEventObserver, 8>::capacity() const;
template s32 soArrayVector<soArticleEventObserver, 8>::size() const;
template void soArrayVector<soArticleEventObserver, 8>::setSize(s32);
