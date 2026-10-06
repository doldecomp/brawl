#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_wnPokeTrainerMBall_ParticleInfo.h>

template wnPokeTrainerMBall::ParticleInfo& soArrayVectorAbstract<wnPokeTrainerMBall::ParticleInfo>::at(s32);
template const wnPokeTrainerMBall::ParticleInfo& soArrayVectorAbstract<wnPokeTrainerMBall::ParticleInfo>::at(s32) const;
template void soArrayVectorAbstract<wnPokeTrainerMBall::ParticleInfo>::unshift(const wnPokeTrainerMBall::ParticleInfo&);
template void soArrayVectorAbstract<wnPokeTrainerMBall::ParticleInfo>::shift();
template void soArrayVectorAbstract<wnPokeTrainerMBall::ParticleInfo>::pop();
template void soArrayVectorAbstract<wnPokeTrainerMBall::ParticleInfo>::insert(s32, const wnPokeTrainerMBall::ParticleInfo&);
template void soArrayVectorAbstract<wnPokeTrainerMBall::ParticleInfo>::set(s32, const wnPokeTrainerMBall::ParticleInfo&, s32);
template bool soArrayVectorAbstract<wnPokeTrainerMBall::ParticleInfo>::isNull() const;
template void soArrayVectorAbstract<wnPokeTrainerMBall::ParticleInfo>::substitution(s32, s32);
