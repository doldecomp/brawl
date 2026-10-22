#pragma once

#include <StaticAssert.h>
#include <ms/ms_message.h>
#include <mu/mu_object.h>

class MuMsg {
public:
    enum AlignMode {
        Align_Center = 0x0,
        Align_Left = 0x1,
        Align_Right = 0x2,
    };

private:
    class WindowSetting {
        char _0[0x48];
    };
    static_assert(sizeof(WindowSetting) == 0x48, "Class is wrong size!");

    bool : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    bool m_isMsgDataSet : 1;
    bool : 1;
    bool : 1;
    bool : 1;
    s8 m_fontId;
    char _2[2];
    void* m_msgData;
    Message* m_message;
    char _12[4];
    u32 m_numMsgs;
    HeapType m_heapType;
    int m_24;

public:
    bool allocMsgBuf(u32 msgSizes, u32 numMsgs);
    void setMsgData(void* msgBinData);
    const char* getMsgData(u32 msgIndex, int* msgLength);
    void initWindowSetting(WindowSetting* windowSetting);
    void attachScnMdlSimple(u32 msgIndex, nw4r::g3d::ScnMdlSimple* sceneModel, u32 boneTextIndex, float fontSize);
    void attachMuObject(u32 lineIndex, MuObject* muObject, const char* format, float f1, float f2, float f3, float f4, float f5);
    void detachMuObject(MuObject* muObject);
    void setFontWidthModeAuto(u32 msgIndex);
    void setFontWidthModeProportional(u32 msgIndex);
    void setFontWidthModeFixed(u32 msgIndex);
    void setAlignMode(u32 msgIndex, AlignMode alignMode);
    void setVerticalMode(u32 msgIndex, bool isVertical);
    void setFontColor(u32 msgIndex, u8 r, u8 g, u8 b, u8 a);
    void setHSpace(u32 msgIndex, float);
    void setWScale(u32 msgIndex, float);
    void getWScale(u32 msgIndex, float);
    void setHScale(u32 msgIndex, float);
    void getHScale(u32 msgIndex, float);
    void setDelayPrint(u32 msgIndex, float, float, float, float);
    bool isEndDelayPrint(u32 index);
    void setEdgeEnable(u32 msgIndex, bool edgeEnable);
    void setEdge(u32 msgIndex, u8 r, u8 g, u8 b, float);
    void setFontType(u32 msgIndex, u32 fontType);
    // void FUN_800b9448(u32 msgIndex, bool);
    // void FUN_800b9460(u32 msgIndex, u8, u8, u8, float);
    void beginPrint(u32 msgIndex);
    void printf(u32 msgIndex, const char* format, ...);
    bool printIndex(u32 msgIndex, u32 lineIndex, void* msgBinData = NULL);
    void setWindowRectVisible(u32 msgIndex, bool isVisible);

    static MuMsg* create(u32 fontSetting, HeapType heapType, HeapType heapType2);
    // CSS: HeapType 1 = 42, HeapType 2 = 43.
    // Game: both 40
    // Photo: both 42
    ~MuMsg();
};
static_assert(sizeof(MuMsg) == 0x1c, "Class is wrong size!");
