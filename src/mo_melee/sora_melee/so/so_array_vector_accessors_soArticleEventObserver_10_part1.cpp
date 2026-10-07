#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soArticleEventObserver.h>

template s32 soArrayVector<soArticleEventObserver, 10>::getTopIndex() const;
template void soArrayVector<soArticleEventObserver, 10>::setTopIndex(s32);
template s32 soArrayVector<soArticleEventObserver, 10>::getLastIndex() const;
template void soArrayVector<soArticleEventObserver, 10>::setLastIndex(s32);
template soArticleEventObserver& soArrayVector<soArticleEventObserver, 10>::getArrayValueConst(s32);
template void soArrayVector<soArticleEventObserver, 10>::onFull();
template void soArrayVector<soArticleEventObserver, 10>::offFull();
template bool soArrayVector<soArticleEventObserver, 10>::isFull() const;
template s32 soArrayVector<soArticleEventObserver, 10>::capacity() const;
template s32 soArrayVector<soArticleEventObserver, 10>::size() const;
template void soArrayVector<soArticleEventObserver, 10>::setSize(s32);
