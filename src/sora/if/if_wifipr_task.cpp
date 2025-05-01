#include <if/if_wifipr_mngr.h>
#include <if/if_wifipr_task.h>
#include <sr/sr_common.h>

char ifWifiprTask::TaskName[] = "ifWifiprTask";

ifWifiprTask* ifWifiprTask::create() {
    ifWifiprTask* task = new (Heaps::InfoInstance) ifWifiprTask;
    task->init();
    task->unk2C_b1 = false;
    return task;
}

void ifWifiprTask::processDefault() {
    g_IfWifiprMngr->main();
}

ifWifiprTask::~ifWifiprTask() { }
