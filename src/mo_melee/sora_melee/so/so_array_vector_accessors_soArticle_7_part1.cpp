#pragma force_active on
#include <so/so_array.h>
class soArticle;

template s32 soArrayVector<soArticle*, 7>::getTopIndex() const;
template void soArrayVector<soArticle*, 7>::setTopIndex(s32);
template s32 soArrayVector<soArticle*, 7>::getLastIndex() const;
template void soArrayVector<soArticle*, 7>::setLastIndex(s32);
template soArticle*& soArrayVector<soArticle*, 7>::getArrayValueConst(s32);
template void soArrayVector<soArticle*, 7>::onFull();
template void soArrayVector<soArticle*, 7>::offFull();
template bool soArrayVector<soArticle*, 7>::isFull() const;
template s32 soArrayVector<soArticle*, 7>::capacity() const;
template s32 soArrayVector<soArticle*, 7>::size() const;
template void soArrayVector<soArticle*, 7>::setSize(s32);
