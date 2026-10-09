#pragma once

#include <gr/gr_yakumono.h>
#include <types.h>

// Battlefield's stage pieces (sky, sun, moon, clouds, platforms, ...): one grBattleField per model of the stage archive.
// Only the piece that owns the "MShadow1" material (the stage's shadow plane) does any work in update().
class grBattleField : public grYakumono {
    u32 m_shadowMatIndex; // material index of "MShadow1" in the first scene model; 0xFF when the model has none

public:
    grBattleField(const char* taskName) : grYakumono(taskName) {
        setupMelee();
        m_noUpdateAnim = true;
        m_shadowMatIndex = 0;
    }
    static grBattleField* create(int mdlIndex, const char* tgtNodeName, const char* taskName);

    virtual void update(float deltaFrame);
    virtual ~grBattleField();
};
static_assert(sizeof(grBattleField) == 0x154, "Class is wrong size!");
