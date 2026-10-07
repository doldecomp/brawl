#pragma force_active on
#include <so/so_array.h>
class soArticle;

template s32 soArrayVector<soArticle*, 20>::size() const;
template s32 soArrayVector<soArticle*, 20>::getTopIndex() const;
template void soArrayVector<soArticle*, 20>::setTopIndex(s32);
template s32 soArrayVector<soArticle*, 20>::getLastIndex() const;
template void soArrayVector<soArticle*, 20>::setLastIndex(s32);
template soArticle*& soArrayVector<soArticle*, 20>::getArrayValueConst(s32);
template void soArrayVector<soArticle*, 20>::onFull();
template void soArrayVector<soArticle*, 20>::offFull();
template bool soArrayVector<soArticle*, 20>::isFull() const;
template s32 soArrayVector<soArticle*, 20>::capacity() const;
template soArticle*& soArrayVector<soArticle*, 20>::atFastAbstractSub(s32) const;
template void soArrayVector<soArticle*, 20>::setSize(s32);
