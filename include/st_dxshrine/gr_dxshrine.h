#pragma once

#include <gr/gr_yakumono.h>
#include <types.h>

class grDxShrine : public grYakumono {
  public:
    grDxShrine(const char* taskName);
	static grDxShrine* create(int mdlIndex, const char *tgtNodeName, const char *taskName);
    virtual ~grDxShrine();
};