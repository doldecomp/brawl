#pragma once

#include <StaticAssert.h>
#include <gr/gr_stadium.h>
#include <ms/ms_message.h>

class grStadiumVision : public grStadium {

public:
    enum MessageDisplay {
        MessageDisplay_None = 0x0,
        MessageDisplay_Ready = 0x1,
        MessageDisplay_Count_5 = 0x2,
        MessageDisplay_Count_4 = 0x3,
        MessageDisplay_Count_3 = 0x4,
        MessageDisplay_Count_2 = 0x5,
        MessageDisplay_Count_1 = 0x6,
        MessageDisplay_Go = 0x7,
        MessageDisplay_SuddenDeath = 0x8,
        MessageDisplay_Time = 0x9,
        MessageDisplay_Success = 0xa,
        MessageDisplay_Failure = 0xb,
        MessageDisplay_Game = 0xc,
        MessageDisplay_Leader = 0xd,
        MessageDisplay_Overview = 0xe,
        MessageDisplay_Defeated_1 = 0xf,
        MessageDisplay_Defeated_2 = 0x10,
        MessageDisplay_Defeated_3 = 0x11,
        MessageDisplay_Defeated_4 = 0x12,
    };

    void* m_msgBinData;
    u8 m_352;
    char _353[3];
    int m_stadiumType;
    MessageDisplay m_messageDisplay : 8;
    char _361[3];
    float _364;
    Message* message;
    float m_372;
    float m_376;
    float m_380;
    float m_384;
    float m_388;
    float m_392;
    float m_396;
    short m_400;
    short m_402;
    short m_404;
    short m_406;
    short m_408;
    short m_410;
    short m_412;
    u8 m_414;
    char _415;

    grStadiumVision(const char* taskName);
    virtual void startup(gfArchive* data, u32 unk1, gfSceneRoot::LayerType layerType);
    virtual void update(float deltaFrame);
    virtual ~grStadiumVision();

    void setDisplay(bool);

    static grStadiumVision* create(int mdlIndex, const char* tgtNodeName, const char* taskName);
};
static_assert(sizeof(grStadiumVision) == 416, "Class is wrong size!");