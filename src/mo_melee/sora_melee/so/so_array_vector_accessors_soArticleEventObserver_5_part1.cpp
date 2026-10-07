#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soArticleEventObserver.h>

template s32 soArrayVector<soArticleEventObserver, 5>::getTopIndex() const;
template void soArrayVector<soArticleEventObserver, 5>::setTopIndex(s32);
template s32 soArrayVector<soArticleEventObserver, 5>::getLastIndex() const;
template void soArrayVector<soArticleEventObserver, 5>::setLastIndex(s32);
template soArticleEventObserver& soArrayVector<soArticleEventObserver, 5>::getArrayValueConst(s32);
template void soArrayVector<soArticleEventObserver, 5>::onFull();
template void soArrayVector<soArticleEventObserver, 5>::offFull();
template bool soArrayVector<soArticleEventObserver, 5>::isFull() const;
template s32 soArrayVector<soArticleEventObserver, 5>::capacity() const;
template s32 soArrayVector<soArticleEventObserver, 5>::size() const;
template void soArrayVector<soArticleEventObserver, 5>::setSize(s32);
