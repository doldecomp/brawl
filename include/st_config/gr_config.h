#pragma once

#include <gr/gr_yakumono.h>
#include <types.h>

class grConfig : public grYakumono {
  public:
    grConfig(const char* taskName);
	static grConfig* create(int mdlIndex, const char *tgtNodeName, const char *taskName);
    virtual ~grConfig();
};