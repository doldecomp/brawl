#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_ftInstanceManager_InstanceInfo.h>

template s32 soArrayVector<ftInstanceManager::InstanceInfo, 16>::getTopIndex() const;
template void soArrayVector<ftInstanceManager::InstanceInfo, 16>::setTopIndex(s32);
template s32 soArrayVector<ftInstanceManager::InstanceInfo, 16>::getLastIndex() const;
template void soArrayVector<ftInstanceManager::InstanceInfo, 16>::setLastIndex(s32);
template ftInstanceManager::InstanceInfo& soArrayVector<ftInstanceManager::InstanceInfo, 16>::getArrayValueConst(s32);
template void soArrayVector<ftInstanceManager::InstanceInfo, 16>::onFull();
template void soArrayVector<ftInstanceManager::InstanceInfo, 16>::offFull();
template bool soArrayVector<ftInstanceManager::InstanceInfo, 16>::isFull() const;
template s32 soArrayVector<ftInstanceManager::InstanceInfo, 16>::capacity() const;
template ftInstanceManager::InstanceInfo& soArrayVector<ftInstanceManager::InstanceInfo, 16>::atFastAbstractSub(s32) const;
template void soArrayVector<ftInstanceManager::InstanceInfo, 16>::setSize(s32);
