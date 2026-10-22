#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <ms/ms_resfont.h>
#include <ms/ms_text_writer_base.h>
#include <nw4r/g3d/g3d_scnmdl.h>
#include <memory.h>

class Message : public ms::TextWriterBase<char> {
public:

    Message(u32, HeapType heapType);
    virtual ~Message();

    char _164[316];

    bool allocMsgBuf(u32 msgSizes, u32 numMsgs, HeapType heapType);
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

    static u32 utf8to16(wchar_t* dst, const char* src);
    static u32 utf16to8(char* dst, const wchar_t* src);
    static void getPrintIndexData(void* msgbin, u32 index, char** outStr, u32* outLen);
    static void drawBoxLine(s32 p1, s32 p2, s32 p3, float f1, float f2, float f3, float f4, float f5);


};
static_assert(sizeof(Message) == 480, "Class is wrong size!");
