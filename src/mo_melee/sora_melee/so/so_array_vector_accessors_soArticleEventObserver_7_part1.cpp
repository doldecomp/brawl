#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_soArticleEventObserver.h>

template s32 soArrayVector<soArticleEventObserver, 7>::getTopIndex() const;
template void soArrayVector<soArticleEventObserver, 7>::setTopIndex(s32);
template s32 soArrayVector<soArticleEventObserver, 7>::getLastIndex() const;
template void soArrayVector<soArticleEventObserver, 7>::setLastIndex(s32);
template soArticleEventObserver& soArrayVector<soArticleEventObserver, 7>::getArrayValueConst(s32);
template void soArrayVector<soArticleEventObserver, 7>::onFull();
template void soArrayVector<soArticleEventObserver, 7>::offFull();
template bool soArrayVector<soArticleEventObserver, 7>::isFull() const;
template s32 soArrayVector<soArticleEventObserver, 7>::capacity() const;
template s32 soArrayVector<soArticleEventObserver, 7>::size() const;
template void soArrayVector<soArticleEventObserver, 7>::setSize(s32);
