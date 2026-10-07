#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_instance_unit.h>
#include <so/templates/so_array_value_soArticleEventObserver.h>

template s32 soArrayVector<soInstanceUnitFullProperty<soArticleEventObserver*>, 10>::getTopIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soArticleEventObserver*>, 10>::setTopIndex(s32);
template s32 soArrayVector<soInstanceUnitFullProperty<soArticleEventObserver*>, 10>::getLastIndex() const;
template void soArrayVector<soInstanceUnitFullProperty<soArticleEventObserver*>, 10>::setLastIndex(s32);
template soInstanceUnitFullProperty<soArticleEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soArticleEventObserver*>, 10>::getArrayValueConst(s32);
template void soArrayVector<soInstanceUnitFullProperty<soArticleEventObserver*>, 10>::onFull();
template void soArrayVector<soInstanceUnitFullProperty<soArticleEventObserver*>, 10>::offFull();
template bool soArrayVector<soInstanceUnitFullProperty<soArticleEventObserver*>, 10>::isFull() const;
template s32 soArrayVector<soInstanceUnitFullProperty<soArticleEventObserver*>, 10>::capacity() const;
template soInstanceUnitFullProperty<soArticleEventObserver*>& soArrayVector<soInstanceUnitFullProperty<soArticleEventObserver*>, 10>::atFastAbstractSub(s32) const;
template void soArrayVector<soInstanceUnitFullProperty<soArticleEventObserver*>, 10>::setSize(s32);
