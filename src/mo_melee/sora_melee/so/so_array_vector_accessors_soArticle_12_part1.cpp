#pragma force_active on
#include <so/so_array.h>
class soArticle;

template s32 soArrayVector<soArticle*, 12>::getTopIndex() const;
template void soArrayVector<soArticle*, 12>::setTopIndex(s32);
template s32 soArrayVector<soArticle*, 12>::getLastIndex() const;
template void soArrayVector<soArticle*, 12>::setLastIndex(s32);
template soArticle*& soArrayVector<soArticle*, 12>::getArrayValueConst(s32);
template void soArrayVector<soArticle*, 12>::onFull();
template void soArrayVector<soArticle*, 12>::offFull();
template bool soArrayVector<soArticle*, 12>::isFull() const;
template s32 soArrayVector<soArticle*, 12>::capacity() const;
template s32 soArrayVector<soArticle*, 12>::size() const;
template void soArrayVector<soArticle*, 12>::setSize(s32);
