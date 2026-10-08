#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <wn/wario/wn_wario_bike_status_uniq_process.h>
#include <wn/wario/wn_wario_bike_link_event.h>
#include <so/so_module_accesser.h>

void wnWarioBikeStatusUniqProcessBump::initStatus(soModuleAccesser* a) {
    soLinkModule& link = a->getLinkModule();
    ftWarioBikeLinkEvent event(0x83e);
    link.sendEventParents(3, event);
}

void wnWarioBikeStatusUniqProcessBump::execFixPos(soModuleAccesser*) {}

wnWarioBikeStatusUniqProcessBump g_wnWarioBikeStatusUniqProcessBump;
