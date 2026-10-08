#pragma once

#include <types.h>

class soModuleAccesser;

// HYPOTHESIS: common interface of the per-fighter "Transactor" singletons (ftRobotTransactor, ftIkeTransactor, ...).
// The default bodies live in sora_melee; the fighters only override the hooks they need. Slots whose purpose is not
// known yet are named after their vtable index.
class ftTransactor {
public:
    virtual ~ftTransactor() { }
    virtual void init(soModuleAccesser* moduleAccesser);
    virtual void exit(soModuleAccesser* moduleAccesser);
    virtual void processUpdate(soModuleAccesser* moduleAccesser);
    virtual void unk4(soModuleAccesser* moduleAccesser);
    virtual void processFixPosition(soModuleAccesser* moduleAccesser);
    virtual void unk6(soModuleAccesser* moduleAccesser);
    virtual void unk7(soModuleAccesser* moduleAccesser);
    virtual void unk8(soModuleAccesser* moduleAccesser);
    virtual bool unk9(soModuleAccesser* moduleAccesser);
    virtual void unk10(soModuleAccesser* moduleAccesser);
    virtual bool unk11(soModuleAccesser* moduleAccesser);
    virtual bool activeArticle(class soArticle* article, soModuleAccesser* moduleAccesser);
    virtual bool unk13(soModuleAccesser* moduleAccesser);
    virtual void unk14(soModuleAccesser* moduleAccesser);
    virtual void unk15(soModuleAccesser* moduleAccesser);
    virtual bool unk16(soModuleAccesser* moduleAccesser);
    virtual void unk17(soModuleAccesser* moduleAccesser);
};
