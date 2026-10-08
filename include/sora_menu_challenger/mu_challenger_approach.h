#pragma once

#include "gf/gf_archive.h"
#include "mu/mu_object.h"
#include "nw4r/g3d/g3d_resfile.h"
#include <gf/gf_task.h>
#include <memory.h>
#include <types.h>

class muChallengerApproachTask : public gfTask {
public:
	// The first 40 bytes are the gfTask base
	
	nw4r::g3d::ResFile m_unk40;	
	nw4r::g3d::ResFile m_unk44;	
	gfTask* m_unk48;
	MuObject* m_unk4C;
	MuObject* m_unk50;

	// Both of these are set in initialize, maybe used elsewhere
	int m_unk54;
	int m_unk58;

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
