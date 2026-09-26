#pragma once

#include <gr/gr_yakumono.h>
#include <types.h>

class grBattleFieldS : public grYakumono {
public:
    grBattleFieldS(const char* taskName) : grYakumono(taskName) {
        setupMelee();
    }
    static grBattleFieldS* create(int mdlIndex, const char* tgtNodeName, const char* taskName);

    virtual ~grBattleFieldS();
};
static_assert(sizeof(grBattleFieldS) == 0x150, "Class is wrong size!");
