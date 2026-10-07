#pragma force_active on
#include <so/so_array.h>
class soArticle;

template s32 soArrayVector<soArticle*, 8>::getTopIndex() const;
template void soArrayVector<soArticle*, 8>::setTopIndex(s32);
template s32 soArrayVector<soArticle*, 8>::getLastIndex() const;
template void soArrayVector<soArticle*, 8>::setLastIndex(s32);
template soArticle*& soArrayVector<soArticle*, 8>::getArrayValueConst(s32);
template void soArrayVector<soArticle*, 8>::onFull();
template void soArrayVector<soArticle*, 8>::offFull();
template bool soArrayVector<soArticle*, 8>::isFull() const;
template s32 soArrayVector<soArticle*, 8>::capacity() const;
template s32 soArrayVector<soArticle*, 8>::size() const;
template void soArrayVector<soArticle*, 8>::setSize(s32);
