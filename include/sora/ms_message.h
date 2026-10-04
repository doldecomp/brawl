#pragma once

// Local description of the menu text writer (class Message) used by MuMsg and ms_message.cpp.
// This intentionally does not include the BrawlHeaders ms_message.h: that header lacks the
// real layout and several members that the game code needs.

#include <ms/ms_char_writer.h>
#include <nw4r/ut/ut_Color.h>
#include <sr/sr_common.h>
#include <stdarg.h>
#include <types.h>

namespace nw4r {
    namespace g3d {
        class ScnMdlSimple;
    }
} // namespace nw4r

struct FontData {
    enum FONT_RESOURCE {
        FONT_SYSTEM = 0,
        FONT_NORMAL = 1,
        FONT_HIRAGANA = 2,
        FONT_ENDING = 3,
        FONT_MELEE = 4,
        FONT_RESETSAN = 5,
        FONT_FOX = 6,
        FONT_ALERT = 7,
        FONT_NORMAL2 = 8,
    };
};

class Message;

// Draw callback registered on a ScnMdlSimple so that a message buffer is drawn with the model.
class msScnObjCallback {
public:
    int m_idx;         // 0x04, index of the message buffer to draw (-1 = base buffer)
    float m_scale;     // 0x08
    Message* m_msg;    // 0x0c
    u8 m_zCompare;     // 0x10
    int m_zUpdate;     // 0x14
    msScnObjCallback* m_next; // 0x18
    void* m_scnMdl;    // 0x1c
    int m_nodeId;      // 0x20
    u8 m_enable;       // 0x24

    msScnObjCallback()
        : m_idx(0)
        , m_scale(1.0f)
        , m_msg(0)
        , m_zCompare(1)
        , m_zUpdate(3)
        , m_next(0)
        , m_enable(1) {}
    virtual ~msScnObjCallback() {}
    virtual void ExecCallback0();
    virtual void ExecCallback1();
    virtual void ExecCallback2();
    virtual void ExecCallback3();
    virtual void ExecCallback4(int pass);
};

// One command buffer for a message (0x54 bytes).
struct MsgBuf {
    int m_rect[4];  // 0x00
    int m_10;       // 0x10
    u8* m_14;       // 0x14
    u8 m_18[4];     // 0x18
    u8 m_1c;        // 0x1c
    u8 m_1d;        // 0x1d
    u8 m_1e[2];
    msScnObjCallback m_cb; // 0x20
    int m_size;     // 0x48
    int m_pos;      // 0x4c
    u8* m_data;     // 0x50
};

namespace ms {
    template <class T>
    class TextWriterBase : public CharWriter {
    public:
        u8 m_70[4];
        float m_74;
        float m_78;
        float m_7c;
        float m_80;
        float m_84;
        u8 m_88[0x14];
        MsgBuf* m_curBuf; // 0x9c
    };
} // namespace ms

// Object at Message+0xa4 (font/tag processor); constructed/destroyed by out-of-line code.
struct MsgTagProc {
    u8 m_data[0x110];
};

class Message : public ms::TextWriterBase<char> {
public:
    virtual ~Message();
    MsgTagProc m_tagProc;   // 0xa4
    nw4r::ut::Color m_1b4;  // 0x1b4
    float m_1b8;
    float m_1bc;
    int m_1c0;
    u8 m_1c4;
    void (*m_1c8)();
    void (*m_1cc)();
    MsgBuf* m_cur;   // 0x1d0
    MsgBuf* m_base;  // 0x1d4
    MsgBuf** m_bufs; // 0x1d8
    int m_numBufs;   // 0x1dc

    Message(u32, Heaps::HeapType heapType);

    bool allocMsgBuf(u32 msgSizes, u32 numMsgs, Heaps::HeapType heapType);
    bool attachMsgBuf(u32 index, nw4r::g3d::ScnMdlSimple* sceneModel, const char* nodeName, u8, int, float);
    bool changeMsgBuf(int index);
    void clearMsgBuf();
    void printMsgBuf(FontData::FONT_RESOURCE fontId);
    void setWindow(float, float, float, float);
    void setCallProjection(u8 p1);
    void setDrawFlag(u32 p1, u32 p2);
    void setFace(u8);
    void setFixedWidth(float);
    void setColor(int);
    void setScale(float);
    void setScale(float, float);
    void setCursorX(float);
    void setCursorY(float);
    void printf(const char* format, ...);

    // Not in the symbol map under a name; named from behaviour.
    void setWindowRect(u32 color, u8 width);
    void setWidthModeAuto(u8 v);
    void setCharSpace(float f1, float f2);
    void setEdge(const GXColor& color, float width);
    void setColor(const GXColor& color);
    void setColor2(const GXColor& color);
    void setColor2(int color);
    void setLineHeight(float h);
    void setSpace(float s);
    void setDelayPrint(float f1, float f2, float f3, float f4);
    void detachMsgBuf(nw4r::g3d::ScnMdlSimple* sceneModel);
    void vprintf(const char* format, va_list args);
    void write(const void* data, int len);
    bool getTag(char** tagOut);
    bool isEndDelayPrint();
    void init(bool, int);
    void writeIndexData(void* msgbin, u32 index);
    void setBufField34(int index, int value);

    static u32 utf8to16(wchar_t* dst, const char* src);
    static u32 utf16to8(char* dst, const wchar_t* src);
    static void getPrintIndexData(void* msgbin, u32 index, char** outStr, u32* outLen);
    static void drawBoxLine(s32 p1, s32 p2, s32 p3, float f1, float f2, float f3, float f4, float f5);
};
