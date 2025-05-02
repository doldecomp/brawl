#include <if/if_adv_mngr.h>
#include <if/if_adv_task.h>
#include <sr/sr_common.h>

char ifAdvTask::TaskName[] = "IfAdvTask";

ifAdvTask* ifAdvTask::create() {
    ifAdvTask* task = new (Heaps::InfoInstance) ifAdvTask;
    task->init();
    task->unk2C_b1 = false;
    return task;
}

void ifAdvTask::processDefault() {
    if (!m_state) {
        s32 res = g_IfAdvMngr->main();
        if (res != 0 && res != 1) {
            m_state = res;
        }
    }
}

void ifAdvTask::renderPre() {
    if (!m_state) {
        g_IfAdvMngr->renderPre();
    }
}

ifAdvTask::~ifAdvTask() { }
