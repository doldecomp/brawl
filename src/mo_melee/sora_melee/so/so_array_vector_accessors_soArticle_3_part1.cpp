#pragma force_active on
#include <so/so_array.h>
class soArticle;

template s32 soArrayVector<soArticle*, 3>::getTopIndex() const;
template void soArrayVector<soArticle*, 3>::setTopIndex(s32);
template s32 soArrayVector<soArticle*, 3>::getLastIndex() const;
template void soArrayVector<soArticle*, 3>::setLastIndex(s32);
template soArticle*& soArrayVector<soArticle*, 3>::getArrayValueConst(s32);
template void soArrayVector<soArticle*, 3>::onFull();
template void soArrayVector<soArticle*, 3>::offFull();
template bool soArrayVector<soArticle*, 3>::isFull() const;
template s32 soArrayVector<soArticle*, 3>::capacity() const;
template s32 soArrayVector<soArticle*, 3>::size() const;
template void soArrayVector<soArticle*, 3>::setSize(s32);
