#include <mu/adv/mu_adv_game_over.h>
#include <sr/sr_common.h>
#include <types.h>

extern "C" muAdvGameOverTask* fn_33_44(muAdvGameOverTask* task,
        const muAdvGameOverTaskParam* param);

muAdvGameOverTask* muAdvGameOverTask::create(const muAdvGameOverTaskParam* param) {
    muAdvGameOverTask* task = static_cast<muAdvGameOverTask*>(
            operator new(0x3F8, Heaps::MenuInstance));
    if (task != nullptr) {
        task = fn_33_44(task, param);
    }
    return task;
}
