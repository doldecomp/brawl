#pragma force_active on
#include <so/so_array.h>
class soArticle;

template s32 soArrayVector<soArticle*, 4>::getTopIndex() const;
template void soArrayVector<soArticle*, 4>::setTopIndex(s32);
template s32 soArrayVector<soArticle*, 4>::getLastIndex() const;
template void soArrayVector<soArticle*, 4>::setLastIndex(s32);
template soArticle*& soArrayVector<soArticle*, 4>::getArrayValueConst(s32);
template void soArrayVector<soArticle*, 4>::onFull();
template void soArrayVector<soArticle*, 4>::offFull();
template bool soArrayVector<soArticle*, 4>::isFull() const;
template s32 soArrayVector<soArticle*, 4>::capacity() const;
template s32 soArrayVector<soArticle*, 4>::size() const;
template void soArrayVector<soArticle*, 4>::setSize(s32);
