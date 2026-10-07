#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soArticleEventObserver.h>

template s32 soArrayVector<soArticleEventObserver, 2>::getTopIndex() const;
template void soArrayVector<soArticleEventObserver, 2>::setTopIndex(s32);
template s32 soArrayVector<soArticleEventObserver, 2>::getLastIndex() const;
template void soArrayVector<soArticleEventObserver, 2>::setLastIndex(s32);
template soArticleEventObserver& soArrayVector<soArticleEventObserver, 2>::getArrayValueConst(s32);
template void soArrayVector<soArticleEventObserver, 2>::onFull();
template void soArrayVector<soArticleEventObserver, 2>::offFull();
template bool soArrayVector<soArticleEventObserver, 2>::isFull() const;
template s32 soArrayVector<soArticleEventObserver, 2>::capacity() const;
template s32 soArrayVector<soArticleEventObserver, 2>::size() const;
template void soArrayVector<soArticleEventObserver, 2>::setSize(s32);
