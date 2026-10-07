#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soArticleEventObserver.h>

template s32 soArrayVector<soArticleEventObserver, 12>::getTopIndex() const;
template void soArrayVector<soArticleEventObserver, 12>::setTopIndex(s32);
template s32 soArrayVector<soArticleEventObserver, 12>::getLastIndex() const;
template void soArrayVector<soArticleEventObserver, 12>::setLastIndex(s32);
template soArticleEventObserver& soArrayVector<soArticleEventObserver, 12>::getArrayValueConst(s32);
template void soArrayVector<soArticleEventObserver, 12>::onFull();
template void soArrayVector<soArticleEventObserver, 12>::offFull();
template bool soArrayVector<soArticleEventObserver, 12>::isFull() const;
template s32 soArrayVector<soArticleEventObserver, 12>::capacity() const;
template s32 soArrayVector<soArticleEventObserver, 12>::size() const;
template void soArrayVector<soArticleEventObserver, 12>::setSize(s32);
