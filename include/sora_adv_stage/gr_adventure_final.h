#pragma once

#include <gr/gr_yakumono.h>

const float EFF_SOMETHING = 0.0f;
const float EFF_FRAME_MAX1 = 2540.0f;
const float EFF_FRAME_MAX2 = 6100.0f;
class grAdventureFinal : public grYakumono {
protected:
    char unk1;
    float unk4;
    u8 m_step;
    u16 padding;

public:
    grAdventureFinal(const char* taskName) : grYakumono(taskName) {
        unk1 = 0;
        unk4 = EFF_SOMETHING;
        m_step = 0;
        setupMelee();
        m_transparencySettings = 0;
    };
    virtual void update(float deltaFrame);
    virtual ~grAdventureFinal();

    virtual void updateEff();

    static grAdventureFinal* create(int mdlIndex, const char* tgtNodeName, const char* taskName);

};
