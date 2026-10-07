#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_wnPokeTrainerMBall_ParticleInfo.h>

template s32 soArrayVector<wnPokeTrainerMBall::ParticleInfo, 2>::getTopIndex() const;
template void soArrayVector<wnPokeTrainerMBall::ParticleInfo, 2>::setTopIndex(s32);
template s32 soArrayVector<wnPokeTrainerMBall::ParticleInfo, 2>::getLastIndex() const;
template void soArrayVector<wnPokeTrainerMBall::ParticleInfo, 2>::setLastIndex(s32);
template wnPokeTrainerMBall::ParticleInfo& soArrayVector<wnPokeTrainerMBall::ParticleInfo, 2>::getArrayValueConst(s32);
template void soArrayVector<wnPokeTrainerMBall::ParticleInfo, 2>::onFull();
template void soArrayVector<wnPokeTrainerMBall::ParticleInfo, 2>::offFull();
template bool soArrayVector<wnPokeTrainerMBall::ParticleInfo, 2>::isFull() const;
template s32 soArrayVector<wnPokeTrainerMBall::ParticleInfo, 2>::capacity() const;
template wnPokeTrainerMBall::ParticleInfo& soArrayVector<wnPokeTrainerMBall::ParticleInfo, 2>::atFastAbstractSub(s32) const;
template void soArrayVector<wnPokeTrainerMBall::ParticleInfo, 2>::setSize(s32);
