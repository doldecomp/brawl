#pragma once

#include "gf/gf_archive.h"
#include "mu/mu_menuroot.h"
#include "mu/mu_object.h"
#include "nw4r/g3d/g3d_resfile.h"
#include <gf/gf_task.h>
#include <memory.h>
#include <types.h>

class muChallengerApproachTask : public gfTask {
public:
	nw4r::g3d::ResFile m_backgroundRes;
	nw4r::g3d::ResFile m_challengerRes;
	MenuRoot* m_menuRoot;
	MuObject* m_backgroundAnim;
	MuObject* m_challengerAnim;
	int m_challengerIndex;
	int m_soundHandle;
	char m_names[14][0x40];
	int m_animState;
	int m_frameCount;

	static muChallengerApproachTask* create();
	muChallengerApproachTask();
	virtual ~muChallengerApproachTask();
	void processDefault();
	void initialize(int);
	void release();
	void createData(gfArchive*);
	
};
static_assert(sizeof(muChallengerApproachTask) == 0x3E4, "Class is wrong size!");
