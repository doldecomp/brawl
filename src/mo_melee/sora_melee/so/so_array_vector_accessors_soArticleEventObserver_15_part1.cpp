#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soArticleEventObserver.h>

template s32 soArrayVector<soArticleEventObserver, 15>::getTopIndex() const;
template void soArrayVector<soArticleEventObserver, 15>::setTopIndex(s32);
template s32 soArrayVector<soArticleEventObserver, 15>::getLastIndex() const;
template void soArrayVector<soArticleEventObserver, 15>::setLastIndex(s32);
template soArticleEventObserver& soArrayVector<soArticleEventObserver, 15>::getArrayValueConst(s32);
template void soArrayVector<soArticleEventObserver, 15>::onFull();
template void soArrayVector<soArticleEventObserver, 15>::offFull();
template bool soArrayVector<soArticleEventObserver, 15>::isFull() const;
template s32 soArrayVector<soArticleEventObserver, 15>::capacity() const;
template s32 soArrayVector<soArticleEventObserver, 15>::size() const;
template void soArrayVector<soArticleEventObserver, 15>::setSize(s32);
