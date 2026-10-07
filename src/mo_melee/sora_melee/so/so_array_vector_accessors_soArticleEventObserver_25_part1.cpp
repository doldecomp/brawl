#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soArticleEventObserver.h>

template s32 soArrayVector<soArticleEventObserver, 25>::getTopIndex() const;
template void soArrayVector<soArticleEventObserver, 25>::setTopIndex(s32);
template s32 soArrayVector<soArticleEventObserver, 25>::getLastIndex() const;
template void soArrayVector<soArticleEventObserver, 25>::setLastIndex(s32);
template soArticleEventObserver& soArrayVector<soArticleEventObserver, 25>::getArrayValueConst(s32);
template void soArrayVector<soArticleEventObserver, 25>::onFull();
template void soArrayVector<soArticleEventObserver, 25>::offFull();
template bool soArrayVector<soArticleEventObserver, 25>::isFull() const;
template s32 soArrayVector<soArticleEventObserver, 25>::capacity() const;
template s32 soArrayVector<soArticleEventObserver, 25>::size() const;
template void soArrayVector<soArticleEventObserver, 25>::setSize(s32);
