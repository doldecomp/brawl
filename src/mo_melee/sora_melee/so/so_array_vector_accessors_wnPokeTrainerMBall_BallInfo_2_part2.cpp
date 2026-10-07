#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_wnPokeTrainerMBall_BallInfo.h>

template s32 soArrayVector<wnPokeTrainerMBall::BallInfo, 2>::getTopIndex() const;
template void soArrayVector<wnPokeTrainerMBall::BallInfo, 2>::setTopIndex(s32);
template s32 soArrayVector<wnPokeTrainerMBall::BallInfo, 2>::getLastIndex() const;
template void soArrayVector<wnPokeTrainerMBall::BallInfo, 2>::setLastIndex(s32);
template wnPokeTrainerMBall::BallInfo& soArrayVector<wnPokeTrainerMBall::BallInfo, 2>::getArrayValueConst(s32);
template void soArrayVector<wnPokeTrainerMBall::BallInfo, 2>::onFull();
template void soArrayVector<wnPokeTrainerMBall::BallInfo, 2>::offFull();
template bool soArrayVector<wnPokeTrainerMBall::BallInfo, 2>::isFull() const;
template s32 soArrayVector<wnPokeTrainerMBall::BallInfo, 2>::capacity() const;
template wnPokeTrainerMBall::BallInfo& soArrayVector<wnPokeTrainerMBall::BallInfo, 2>::atFastAbstractSub(s32) const;
template void soArrayVector<wnPokeTrainerMBall::BallInfo, 2>::setSize(s32);
