#pragma force_active on
#include <so/so_array.h>
class soArticle;

template s32 soArrayVector<soArticle*, 24>::size() const;
template s32 soArrayVector<soArticle*, 24>::getTopIndex() const;
template void soArrayVector<soArticle*, 24>::setTopIndex(s32);
template s32 soArrayVector<soArticle*, 24>::getLastIndex() const;
template void soArrayVector<soArticle*, 24>::setLastIndex(s32);
template soArticle*& soArrayVector<soArticle*, 24>::getArrayValueConst(s32);
template void soArrayVector<soArticle*, 24>::onFull();
template void soArrayVector<soArticle*, 24>::offFull();
template bool soArrayVector<soArticle*, 24>::isFull() const;
template s32 soArrayVector<soArticle*, 24>::capacity() const;
template soArticle*& soArrayVector<soArticle*, 24>::atFastAbstractSub(s32) const;
template void soArrayVector<soArticle*, 24>::setSize(s32);
