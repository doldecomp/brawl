#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_wnPokeTrainerMBall_BallInfo.h>

template wnPokeTrainerMBall::BallInfo& soArrayVectorAbstract<wnPokeTrainerMBall::BallInfo>::at(s32);
template const wnPokeTrainerMBall::BallInfo& soArrayVectorAbstract<wnPokeTrainerMBall::BallInfo>::at(s32) const;
template void soArrayVectorAbstract<wnPokeTrainerMBall::BallInfo>::unshift(const wnPokeTrainerMBall::BallInfo&);
template void soArrayVectorAbstract<wnPokeTrainerMBall::BallInfo>::shift();
template void soArrayVectorAbstract<wnPokeTrainerMBall::BallInfo>::pop();
template void soArrayVectorAbstract<wnPokeTrainerMBall::BallInfo>::insert(s32, const wnPokeTrainerMBall::BallInfo&);
template void soArrayVectorAbstract<wnPokeTrainerMBall::BallInfo>::set(s32, const wnPokeTrainerMBall::BallInfo&, s32);
template bool soArrayVectorAbstract<wnPokeTrainerMBall::BallInfo>::isNull() const;
template void soArrayVectorAbstract<wnPokeTrainerMBall::BallInfo>::substitution(s32, s32);
