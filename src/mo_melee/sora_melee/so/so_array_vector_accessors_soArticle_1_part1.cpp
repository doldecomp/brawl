#pragma force_active on
#include <so/so_array.h>
class soArticle;

template s32 soArrayVector<soArticle*, 1>::getTopIndex() const;
template void soArrayVector<soArticle*, 1>::setTopIndex(s32);
template s32 soArrayVector<soArticle*, 1>::getLastIndex() const;
template void soArrayVector<soArticle*, 1>::setLastIndex(s32);
template soArticle*& soArrayVector<soArticle*, 1>::getArrayValueConst(s32);
template void soArrayVector<soArticle*, 1>::onFull();
template void soArrayVector<soArticle*, 1>::offFull();
template bool soArrayVector<soArticle*, 1>::isFull() const;
template s32 soArrayVector<soArticle*, 1>::capacity() const;
template s32 soArrayVector<soArticle*, 1>::size() const;
template void soArrayVector<soArticle*, 1>::setSize(s32);
