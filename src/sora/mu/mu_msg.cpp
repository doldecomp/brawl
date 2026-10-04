#include <gf/gf_heap_manager.h>
#include <nw4r/g3d/g3d_scnmdlsmpl.h>
#include <sora/ms_message.h>
#include <sr/sr_common.h>
#include <stdio.h>
#include <types.h>

// Font manager (global object) used to load/release the font used by a MuMsg.
extern u8 lbl_8049E01C[];
extern "C" u8 fn_800B8648(void* mgr, u32 fontSetting, int p2, int p3);
extern "C" void fn_800B881C(void* mgr, u8 fontId);

class MuObject;
extern "C" int lbl_805A0178;

class MuMsg {
public:
    enum AlignMode {
        Align_Center = 0x0,
        Align_Left = 0x1,
        Align_Right = 0x2,
    };

    class WindowSetting {
    public:
        u32 m_rectVisible : 1;
        u32 m_alignMode : 2;
        u32 m_vertical : 1;
        u32 m_widthMode : 2;
        u32 m_edgeEnable : 1;
        u32 m_fontType : 3;
        u32 : 22;
        float m_x;           // 0x04
        float m_y;           // 0x08
        float m_w;           // 0x0c
        float m_h;           // 0x10
        GXColor m_fontColor; // 0x14
        GXColor m_edgeColor; // 0x18
        float m_fixedWidth;  // 0x1c
        float m_edgeWidth;   // 0x20
        float m_hSpace;      // 0x24
        float m_wScale;      // 0x28
        float m_lineHeight;  // 0x2c
        float m_hScale;      // 0x30
        float m_hScale2;     // 0x34
        float m_delay[4];    // 0x38

        WindowSetting() {
            m_x = 0.0f;
            m_y = 0.0f;
            m_w = 0.0f;
            m_h = 0.0f;
        }
        ~WindowSetting() {}
    };

    u8 m_isMsgDataSet : 1;
    u8 : 7;
    u8 m_fontId;
    void* m_msgData;
    Message* m_message;
    WindowSetting* m_windows;
    u32 m_numMsgs;
    Heaps::HeapType m_heapType;
    u32 m_heapType2;

    bool allocMsgBuf(u32 msgSizes, u32 numMsgs);
    void setMsgData(void* msgBinData);
    const char* getMsgData(u32 msgIndex, int* msgLength);
    void initWindowSetting(WindowSetting* windowSetting);
    void attachScnMdlSimple(u32 msgIndex, nw4r::g3d::ScnMdlSimple* sceneModel, u32 boneTextIndex, float fontSize);
    void attachMuObject(u32 lineIndex, MuObject* muObject, const char* format, float f1, float f2, float f3, float f4, float f5);
    void detachMuObject(MuObject* muObject);
    void setFontWidthModeAuto(u32 msgIndex);
    void setFontWidthModeProportional(u32 msgIndex);
    void setFontWidthModeFixed(u32 msgIndex, float width);
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
    void beginPrint(u32 msgIndex);
    void printData(u32 msgIndex, const void* data, int len);
    void endPrint();
    bool getTag(u32 msgIndex, char** tagOut);
    void printf(u32 msgIndex, const char* format, ...);
    bool printIndex(u32 msgIndex, u32 lineIndex, void* msgBinData = NULL);
    void setWindowRectVisible(u32 msgIndex, bool isVisible);

    static MuMsg* create(u32 fontSetting, Heaps::HeapType heapType, u32 heapType2);
    ~MuMsg();
};

MuMsg* MuMsg::create(u32 fontSetting, Heaps::HeapType heapType, u32 heapType2) {
    MuMsg* msg = new (heapType) MuMsg;
    if (msg != NULL) {
        msg->m_isMsgDataSet = 0;
        msg->m_msgData = NULL;
        msg->m_message = new (heapType) Message(0, heapType);
        if (fontSetting != 0) {
            msg->m_fontId = fn_800B8648(lbl_8049E01C, fontSetting, 0xff, 0);
        } else {
            msg->m_fontId = 0xff;
        }
        msg->m_windows = NULL;
        msg->m_numMsgs = 0;
        msg->m_heapType = heapType;
        msg->m_heapType2 = heapType2;
    }
    return msg;
}

MuMsg::~MuMsg() {
    if (m_fontId != 0xff) {
        fn_800B881C(lbl_8049E01C, m_fontId);
    }
    if (m_msgData != NULL && !m_isMsgDataSet) {
        gfHeapManager::free(m_msgData);
    }
    if (m_windows != NULL) {
        delete[] m_windows;
    }
    delete m_message;
}

bool MuMsg::allocMsgBuf(u32 msgSizes, u32 numMsgs) {
    if (!m_message->allocMsgBuf(msgSizes, numMsgs, m_heapType)) {
        return false;
    }
    int i;
    WindowSetting* ws = new (m_heapType) WindowSetting[numMsgs];
    m_windows = ws;
    i = 0;
    m_numMsgs = numMsgs;
    for (; i < (int)numMsgs; i++, ws++) {
        initWindowSetting(ws);
    }
    return true;
}

void MuMsg::initWindowSetting(WindowSetting* ws) {
    ws->m_rectVisible = 0;
    ws->m_alignMode = 0;
    ws->m_vertical = 0;
    ws->m_widthMode = 0;
    ws->m_edgeEnable = 0;
    ws->m_x = 0.0f;
    ws->m_y = 0.0f;
    ws->m_w = 64.0f;
    ws->m_h = 64.0f;
    ws->m_fontColor.r = 0xff;
    ws->m_fontColor.g = 0xff;
    ws->m_fontColor.b = 0xff;
    ws->m_fontColor.a = 0xff;
    ws->m_fontType = 0;
    ws->m_fixedWidth = 32.0f;
    ws->m_edgeWidth = 1.3f;
    ws->m_edgeColor.r = 0;
    ws->m_edgeColor.g = 0;
    ws->m_edgeColor.b = 0;
    ws->m_edgeColor.a = 0xff;
    ws->m_hSpace = 0.0f;
    ws->m_wScale = 0.8f;
    ws->m_lineHeight = -1.0f;
    ws->m_hScale = 1.0f;
    ws->m_hScale2 = 1.0f;
    ws->m_delay[0] = -1.0f;
    ws->m_delay[1] = 0.0f;
    ws->m_delay[2] = 0.0f;
    ws->m_delay[3] = 0.0f;
}

void MuMsg::setMsgData(void* msgBinData) {
    m_msgData = msgBinData;
    m_isMsgDataSet = 1;
}

void MuMsg::attachScnMdlSimple(u32 msgIndex, nw4r::g3d::ScnMdlSimple* sceneModel, u32 boneTextIndex, float fontSize) {
    char name[0x20];
    sprintf(name, "textN%d", boneTextIndex);
    m_message->attachMsgBuf(msgIndex, sceneModel, name, 0, 3, fontSize);
    WindowSetting* ws = &m_windows[msgIndex];
    initWindowSetting(ws);
    nw4r::g3d::ResMdl resMdl = sceneModel->m_resMdl;
    sprintf(name, "textL%d", boneTextIndex);
    nw4r::g3d::ResNode node = resMdl.GetResNode(name);
    Vec3f pos;
    pos = node.ptr()->m_translation;
    sprintf(name, "textR%d", boneTextIndex);
    node = resMdl.GetResNode(name);
    Vec3f pos2;
    pos2 = node.ptr()->m_translation;
    float scale = 1.0f / fontSize;
    ws->m_x = pos.m_x * scale;
    ws->m_y = -pos.m_y * scale;
    ws->m_w = pos2.m_x * scale;
    ws->m_h = -pos2.m_y * scale;
}

void MuMsg::attachMuObject(u32 lineIndex, MuObject* muObject, const char* format, float f1, float f2, float f3, float f4, float f5) {
    m_message->attachMsgBuf(lineIndex, (nw4r::g3d::ScnMdlSimple*)((u32*)muObject)[4], format, 1, 3, f5);
    WindowSetting* ws = &m_windows[lineIndex];
    initWindowSetting(ws);
    float scale = 1.0f / f5;
    ws->m_x = f1 * scale;
    ws->m_y = f2 * scale;
    ws->m_w = f3 * scale;
    ws->m_h = f4 * scale;
}

void MuMsg::detachMuObject(MuObject* muObject) {
    m_message->detachMsgBuf((nw4r::g3d::ScnMdlSimple*)((u32*)muObject)[4]);
}

void MuMsg::beginPrint(u32 msgIndex) {
    WindowSetting* ws = &m_windows[msgIndex];
    m_message->changeMsgBuf(msgIndex);
    m_message->clearMsgBuf();
    m_message->setWindow(ws->m_x, ws->m_y, ws->m_w, ws->m_h);
    if (ws->m_rectVisible) {
        m_message->setWindowRect(0xFFFF00FF, 8);
    }
    switch (ws->m_alignMode) {
    case 0:
        m_message->setDrawFlag(1, 3);
        break;
    case 1:
        m_message->setDrawFlag(0, 3);
        break;
    case 2:
        m_message->setDrawFlag(2, 3);
        break;
    }
    switch (ws->m_vertical) {
    case 0:
        m_message->setDrawFlag(0x100, 0x300);
        break;
    case 1:
        m_message->setDrawFlag(0, 0x300);
        break;
    }
    m_message->setCharSpace(ws->m_wScale, 0.5f);
    m_message->setScale(ws->m_hScale, ws->m_hScale2);
    switch (ws->m_widthMode) {
    case 0:
        m_message->setFixedWidth(-1.0f);
        m_message->setWidthModeAuto(1);
        break;
    case 1:
        m_message->setFixedWidth(-1.0f);
        break;
    case 2:
        m_message->setFixedWidth(ws->m_fixedWidth);
        break;
    }
    switch (ws->m_fontType) {
    case 1:
        m_message->setFace(2);
        break;
    case 4:
        m_message->setFace(4);
        break;
    case 3:
        m_message->setFace(3);
        break;
    case 5:
        m_message->setFace(6);
        break;
    case 6:
        m_message->setFace(5);
        break;
    case 0:
    case 2:
    default:
        {
            Message* msg = m_message;
            if (lbl_805A0178 != 0) {
                msg->setFace(8);
            } else {
                msg->setFace(1);
            }
        }
        break;
    }
    if (ws->m_edgeEnable) {
        m_message->setEdge(ws->m_edgeColor, ws->m_edgeWidth);
    }
    m_message->setColor(ws->m_fontColor);
    m_message->setColor2(ws->m_fontColor);
    if (ws->m_lineHeight >= 0.0f) {
        m_message->setLineHeight(ws->m_lineHeight);
    }
    m_message->setSpace(ws->m_hSpace);
    if (ws->m_delay[0] >= 0.0f) {
        m_message->setDelayPrint(ws->m_delay[0], ws->m_delay[1], ws->m_delay[2], ws->m_delay[3]);
    }
}

bool MuMsg::printIndex(u32 msgIndex, u32 lineIndex, void* msgBinData) {
    if (msgBinData == NULL) {
        msgBinData = m_msgData;
        if (msgBinData == NULL) {
            return false;
        }
    }
    beginPrint(msgIndex);
    m_message->writeIndexData(msgBinData, lineIndex);
    return true;
}

void MuMsg::printf(u32 msgIndex, const char* format, ...) {
    beginPrint(msgIndex);
    va_list args;
    va_start(args, format);
    m_message->vprintf(format, args);
}

void MuMsg::printData(u32 msgIndex, const void* data, int len) {
    beginPrint(msgIndex);
    m_message->write(data, len);
}

void MuMsg::endPrint() {
    MsgBuf* buf = m_message->m_cur;
    buf->m_data[buf->m_pos] = 1;
}

const char* MuMsg::getMsgData(u32 msgIndex, int* msgLength) {
    char* str;
    u32 len;
    Message::getPrintIndexData(m_msgData, msgIndex, &str, &len);
    *msgLength = len;
    return str;
}

void MuMsg::setWindowRectVisible(u32 msgIndex, bool isVisible) {
    m_windows[msgIndex].m_rectVisible = isVisible;
}

void MuMsg::setFontColor(u32 msgIndex, u8 r, u8 g, u8 b, u8 a) {
    WindowSetting* ws = &m_windows[msgIndex];
    ws->m_fontColor.r = r;
    ws->m_fontColor.g = g;
    ws->m_fontColor.b = b;
    ws->m_fontColor.a = a;
}

void MuMsg::setAlignMode(u32 msgIndex, AlignMode alignMode) {
    m_windows[msgIndex].m_alignMode = alignMode;
}

void MuMsg::setVerticalMode(u32 msgIndex, bool isVertical) {
    m_windows[msgIndex].m_vertical = isVertical;
}

void MuMsg::setFontWidthModeAuto(u32 msgIndex) {
    m_windows[msgIndex].m_widthMode = 0;
}

void MuMsg::setFontWidthModeProportional(u32 msgIndex) {
    m_windows[msgIndex].m_widthMode = 1;
}

void MuMsg::setFontWidthModeFixed(u32 msgIndex, float width) {
    WindowSetting* ws = &m_windows[msgIndex];
    ws->m_widthMode = 2;
    ws->m_fixedWidth = width;
}

void MuMsg::setEdgeEnable(u32 msgIndex, bool edgeEnable) {
    m_windows[msgIndex].m_edgeEnable = edgeEnable;
}

void MuMsg::setEdge(u32 msgIndex, u8 r, u8 g, u8 b, float width) {
    WindowSetting* ws = &m_windows[msgIndex];
    ws->m_edgeWidth = width;
    ws->m_edgeColor.r = r;
    ws->m_edgeColor.g = g;
    ws->m_edgeColor.b = b;
    ws->m_edgeColor.a = 0xff;
}

void MuMsg::setFontType(u32 msgIndex, u32 fontType) {
    m_windows[msgIndex].m_fontType = fontType;
}

void MuMsg::setHSpace(u32 msgIndex, float v) {
    m_windows[msgIndex].m_hSpace = v;
}

void MuMsg::setWScale(u32 msgIndex, float v) {
    m_windows[msgIndex].m_wScale = v;
}

void MuMsg::getWScale(u32 msgIndex, float v) {
    m_windows[msgIndex].m_lineHeight = v;
}

void MuMsg::setHScale(u32 msgIndex, float v) {
    m_windows[msgIndex].m_hScale = v;
}

void MuMsg::getHScale(u32 msgIndex, float v) {
    m_windows[msgIndex].m_hScale2 = v;
}

void MuMsg::setDelayPrint(u32 msgIndex, float f1, float f2, float f3, float f4) {
    WindowSetting* ws = &m_windows[msgIndex];
    ws->m_delay[0] = f1;
    ws->m_delay[1] = f2;
    ws->m_delay[2] = f3;
    ws->m_delay[3] = f4;
}

bool MuMsg::isEndDelayPrint(u32 msgIndex) {
    m_message->changeMsgBuf(msgIndex);
    return m_message->isEndDelayPrint();
}

bool MuMsg::getTag(u32 msgIndex, char** tagOut) {
    m_message->changeMsgBuf(msgIndex);
    return m_message->getTag(tagOut);
}
