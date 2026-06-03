#pragma once

#include <gr/gr_yakumono.h>

const float EFF_SOMETHING = 0.0f;
const float EFF_FRAME_MAX1 = 2540.0f;
const float EFF_FRAME_MAX2 = 6100.0f;
class grTengan : public grYakumono {
protected:
    char m_tgtNode[0x80];
//    float unk_float;
//    u8 type;
//    u8 step;
//    u16 padding;

public:
    grTengan(const char* taskName);
    virtual void update(float deltaFrame);
    virtual ~grTengan();

    virtual void setTgtNode(const char *tgtNode);
    virtual char* getTgtNode();

    static grTengan* create(int mdlIndex, const char* tgtNodeName, const char* taskName);

};
