#pragma force_active on
#include <so/so_array.h>
class soArticle;

template s32 soArrayVector<soArticle*, 25>::getTopIndex() const;
template void soArrayVector<soArticle*, 25>::setTopIndex(s32);
template s32 soArrayVector<soArticle*, 25>::getLastIndex() const;
template void soArrayVector<soArticle*, 25>::setLastIndex(s32);
template soArticle*& soArrayVector<soArticle*, 25>::getArrayValueConst(s32);
template void soArrayVector<soArticle*, 25>::onFull();
template void soArrayVector<soArticle*, 25>::offFull();
template bool soArrayVector<soArticle*, 25>::isFull() const;
template s32 soArrayVector<soArticle*, 25>::capacity() const;
template s32 soArrayVector<soArticle*, 25>::size() const;
template void soArrayVector<soArticle*, 25>::setSize(s32);
