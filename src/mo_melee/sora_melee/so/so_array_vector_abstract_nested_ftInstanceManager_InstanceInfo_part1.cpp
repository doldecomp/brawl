#pragma force_active on
#include <so/so_array.h>
#include <so/templates/so_array_value_ftInstanceManager_InstanceInfo.h>

template void soArrayVectorAbstract<ftInstanceManager::InstanceInfo>::push(const ftInstanceManager::InstanceInfo&);
template void soArrayVectorAbstract<ftInstanceManager::InstanceInfo>::erase(s32);
template void soArrayVectorAbstract<ftInstanceManager::InstanceInfo>::clear();
