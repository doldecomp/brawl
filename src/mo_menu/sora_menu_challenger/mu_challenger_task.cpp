#include <sora_menu_challenger/mu_challenger_task.h>

muChallengerApproachTask* muChallengerApproachTask::create() {
    return new (Heaps::MenuInstance) muChallengerApproachTask();
}
