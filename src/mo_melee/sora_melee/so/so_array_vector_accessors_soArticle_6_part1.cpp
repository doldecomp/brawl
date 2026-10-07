#pragma force_active on
#include <so/so_array.h>
class soArticle;

template s32 soArrayVector<soArticle*, 6>::getTopIndex() const;
template void soArrayVector<soArticle*, 6>::setTopIndex(s32);
template s32 soArrayVector<soArticle*, 6>::getLastIndex() const;
template void soArrayVector<soArticle*, 6>::setLastIndex(s32);
template soArticle*& soArrayVector<soArticle*, 6>::getArrayValueConst(s32);
template void soArrayVector<soArticle*, 6>::onFull();
template void soArrayVector<soArticle*, 6>::offFull();
template bool soArrayVector<soArticle*, 6>::isFull() const;
template s32 soArrayVector<soArticle*, 6>::capacity() const;
template s32 soArrayVector<soArticle*, 6>::size() const;
template void soArrayVector<soArticle*, 6>::setSize(s32);
