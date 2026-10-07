#pragma once

#include <gf/gf_task.h>
#include <memory.h>
#include <types.h>

class muChallengerApproachTask : public gfTask {
public:
	char _unk40[0x3A4];

	muChallengerApproachTask();
	static muChallengerApproachTask* create();

	virtual ~muChallengerApproachTask();
	
};
static_assert(sizeof(muChallengerApproachTask) == 0x3E4, "Class is wrong size!");
