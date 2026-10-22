#pragma once

#include <gr/gr_yakumono.h>

const float EFF_SOMETHING = 0.0f;
const float EFF_FRAME_MAX1 = 2540.0f;
const float EFF_FRAME_MAX2 = 6100.0f;
class grFinal : public grYakumono {
protected:
    char unk1;
    float unk4;
    u8 m_type;
    u8 m_step;
    u16 m_padding;

public:
    grFinal(const char* taskName) : grYakumono(taskName) {
        unk1 = 0;
        unk4 = EFF_SOMETHING;
        m_type = 0;
        m_step = 0;
        setupMelee();
    };
    virtual void update(float deltaFrame);
    virtual ~grFinal();

    virtual void updateEff();
    virtual void setType(int type);

    static grFinal* create(int mdlIndex, const char* tgtNodeName, const char* taskName);

};
