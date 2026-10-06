#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_ftInstanceManager_InstanceInfo.h>

template ftInstanceManager::InstanceInfo& soArrayVectorAbstract<ftInstanceManager::InstanceInfo>::at(s32);
template const ftInstanceManager::InstanceInfo& soArrayVectorAbstract<ftInstanceManager::InstanceInfo>::at(s32) const;
template void soArrayVectorAbstract<ftInstanceManager::InstanceInfo>::unshift(const ftInstanceManager::InstanceInfo&);
template void soArrayVectorAbstract<ftInstanceManager::InstanceInfo>::shift();
template void soArrayVectorAbstract<ftInstanceManager::InstanceInfo>::pop();
template void soArrayVectorAbstract<ftInstanceManager::InstanceInfo>::insert(s32, const ftInstanceManager::InstanceInfo&);
template void soArrayVectorAbstract<ftInstanceManager::InstanceInfo>::set(s32, const ftInstanceManager::InstanceInfo&, s32);
template bool soArrayVectorAbstract<ftInstanceManager::InstanceInfo>::isNull() const;
template void soArrayVectorAbstract<ftInstanceManager::InstanceInfo>::substitution(s32, s32);
