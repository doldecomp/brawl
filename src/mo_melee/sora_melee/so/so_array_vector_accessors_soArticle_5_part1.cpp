#pragma force_active on
#include <so/so_array.h>
class soArticle;

template s32 soArrayVector<soArticle*, 5>::getTopIndex() const;
template void soArrayVector<soArticle*, 5>::setTopIndex(s32);
template s32 soArrayVector<soArticle*, 5>::getLastIndex() const;
template void soArrayVector<soArticle*, 5>::setLastIndex(s32);
template soArticle*& soArrayVector<soArticle*, 5>::getArrayValueConst(s32);
template void soArrayVector<soArticle*, 5>::onFull();
template void soArrayVector<soArticle*, 5>::offFull();
template bool soArrayVector<soArticle*, 5>::isFull() const;
template s32 soArrayVector<soArticle*, 5>::capacity() const;
template s32 soArrayVector<soArticle*, 5>::size() const;
template void soArrayVector<soArticle*, 5>::setSize(s32);
