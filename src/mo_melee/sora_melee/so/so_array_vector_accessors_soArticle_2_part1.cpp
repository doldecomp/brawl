#pragma force_active on
#include <so/so_array.h>
class soArticle;

template s32 soArrayVector<soArticle*, 2>::getTopIndex() const;
template void soArrayVector<soArticle*, 2>::setTopIndex(s32);
template s32 soArrayVector<soArticle*, 2>::getLastIndex() const;
template void soArrayVector<soArticle*, 2>::setLastIndex(s32);
template soArticle*& soArrayVector<soArticle*, 2>::getArrayValueConst(s32);
template void soArrayVector<soArticle*, 2>::onFull();
template void soArrayVector<soArticle*, 2>::offFull();
template bool soArrayVector<soArticle*, 2>::isFull() const;
template s32 soArrayVector<soArticle*, 2>::capacity() const;
template s32 soArrayVector<soArticle*, 2>::size() const;
template void soArrayVector<soArticle*, 2>::setSize(s32);
