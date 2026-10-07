#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soArticleEventObserver.h>

template s32 soArrayVector<soArticleEventObserver, 6>::getTopIndex() const;
template void soArrayVector<soArticleEventObserver, 6>::setTopIndex(s32);
template s32 soArrayVector<soArticleEventObserver, 6>::getLastIndex() const;
template void soArrayVector<soArticleEventObserver, 6>::setLastIndex(s32);
template soArticleEventObserver& soArrayVector<soArticleEventObserver, 6>::getArrayValueConst(s32);
template void soArrayVector<soArticleEventObserver, 6>::onFull();
template void soArrayVector<soArticleEventObserver, 6>::offFull();
template bool soArrayVector<soArticleEventObserver, 6>::isFull() const;
template s32 soArrayVector<soArticleEventObserver, 6>::capacity() const;
template s32 soArrayVector<soArticleEventObserver, 6>::size() const;
template void soArrayVector<soArticleEventObserver, 6>::setSize(s32);
