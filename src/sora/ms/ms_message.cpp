#include <gf/gf_application.h>
#include <gf/gf_heap_manager.h>
#include <nw4r/g3d/g3d_scnmdlsmpl.h>
#include <revolution/GX.h>
#include <revolution/MTX.h>
#include <sora/ms_message.h>
#include <sr/sr_common.h>
#include <stdio.h>
#include <string.h>
#include <types.h>

extern int lbl_805A0174;
extern int lbl_805A0178;

static void drawCallbackProjection();

Message::Message(u32 bufSize, Heaps::HeapType heapType) {
    SetTagProcessor(&m_tagProc);
    SetFlags(0);
    EnableFixedWidth(true);
    SetFixedWidth(32.0f);
    m_numBufs = 0;
    m_bufs = NULL;
    m_base = NULL;
    if (bufSize != 0) {
        MsgBuf* buf = new (heapType) MsgBuf(bufSize, heapType);
        m_base = buf;
        buf->m_size = bufSize;
        changeMsgBuf(-1);
        clearMsgBuf();
        m_1c8 = drawCallbackProjection;
        m_1cc = drawCallbackProjection;
    }
    m_1c4 = 1;
}

Message::~Message() {
    delete m_base;
    if (m_bufs != NULL) {
        while (m_numBufs != 0) {
            m_numBufs--;
            MsgBuf* buf = m_bufs[m_numBufs];
            delete buf;
            m_bufs[m_numBufs] = NULL;
        }
        gfHeapManager::free(m_bufs);
        m_bufs = NULL;
    }
}

void Message::setCursorX(float x) {
    put(0x16);
    put(1);
    u8 tmp[4];
    putBytes(floatToBytes(tmp, x), 4);
}

void Message::setCursorY(float y) {
    put(0x16);
    put(2);
    u8 tmp[4];
    putBytes(floatToBytes(tmp, y), 4);
}

void Message::setWindow(float f1, float f2, float f3, float f4) {
    put(0x17);
    u8 tmp[2];
    putBytes(floatToShortBytes(tmp, f1), 2);
    putBytes(floatToShortBytes(tmp, f2), 2);
    putBytes(floatToShortBytes(tmp, f3), 2);
    putBytes(floatToShortBytes(tmp, f4), 2);
}

void Message::setCallProjection(u8 p1) {
    put(0x1a);
    put(p1);
}

void Message::setWindowRect(u32 color, u8 width) {
    put(0x19);
    MsgBuf* buf = m_cur;
    for (int i = 0; i < 4; i++) {
        buf->m_data[buf->m_pos++] = color >> (24 - 8 * i);
    }
    put(width);
}

void Message::setWidthModeAuto(u8 v) {
    put(5);
    put(v);
}

void Message::printf(const char* format, ...) {
    va_list args;
    va_start(args, format);
    char* buf = (char*)__alloca(GetBufferSize());
    int len = vsnprintf(buf, GetBufferSize(), format, args);
    MsgBuf* cur = m_cur;
    memcpy(cur->m_data + cur->m_pos, buf, len);
    cur->m_pos += len;
}

void Message::vprintf(const char* format, va_list args) {
    char* buf = (char*)__alloca(GetBufferSize());
    int len = vsnprintf(buf, GetBufferSize(), format, args);
    MsgBuf* cur = m_cur;
    memcpy(cur->m_data + cur->m_pos, buf, len);
    cur->m_pos += len;
}

void Message::write(const void* data, int len) {
    MsgBuf* cur = m_cur;
    memcpy(cur->m_data + cur->m_pos, data, len);
    cur->m_pos += len;
}

void Message::writeString(const char* str) {
    int len = strlen(str);
    MsgBuf* cur = m_cur;
    memcpy(cur->m_data + cur->m_pos, str, len);
    cur->m_pos += len;
}

void Message::setScale(float scale) {
    if (scale > 4.0f) {
        scale = 3.99f;
    }
    put(0xd);
    int v = (int)(64.0f * scale);
    put(v);
    put(v);
}

void Message::setScale(float x, float y) {
    if (x > 4.0f) {
        x = 3.99f;
    }
    if (y > 4.0f) {
        y = 3.99f;
    }
    int vx = (int)(64.0f * x);
    int vy = (int)(64.0f * y);
    put(0xd);
    put(vx);
    put(vy);
}

void Message::setLineHeight(float h) {
    int v = (int)h;
    put(0xe);
    put(v);
}

void Message::setSpace(float s) {
    put(3);
    int v = (int)(256.0f * s);
    put((u32)v >> 8);
    put(v);
}

void Message::setColor(const GXColor& c) {
    put(0xc);
    put(c.r);
    put(c.g);
    put(c.b);
    put(c.a);
}

void Message::setColor(int c) {
    put(0xc);
    put((u32)c >> 24);
    put((u32)c >> 16);
    put((u32)c >> 8);
    put(c);
}

void Message::setColor2(const GXColor& c) {
    put(4);
    put(c.r);
    put(c.g);
    put(c.b);
    put(c.a);
}

void Message::setColor2(int c) {
    put(4);
    put((u32)c >> 24);
    put((u32)c >> 16);
    put((u32)c >> 8);
    put(c);
}

void Message::setCharSpace(float f1, float f2) {
    if (f2 > 4.0f) {
        f2 = 3.99f;
    }
    int a = (int)(64.0f * f2);
    int v = (int)(256.0f * f1);
    put(0x1d);
    put(a);
    put(0x1c);
    put((u32)v >> 8);
    put(v);
}

int Message::writeTagClear(char* dst) {
    dst[0] = 0x12;
    dst[1] = 0x80;
    return 2;
}

void Message::setEdge(const GXColor& c, float width) {
    u32 rgb = (c.r << 24) + (c.g << 16) + (c.b << 8);
    put(0x11);
    put((int)(20.0f * width));
    put(rgb >> 24);
    put(rgb >> 16);
    put(rgb >> 8);
}

void Message::setFace(u8 face) {
    put(2);
    put(face);
}

void Message::setDrawFlag(u32 a, u32 b) {
    put(0x18);
    put(((a & 0x300) >> 4) + ((a & 3) + ((a & 0x30) >> 2)));
    put(((b & 0x300) >> 4) + ((b & 3) + ((b & 0x30) >> 2)));
}

void Message::setFixedWidth(float w) {
    put(0xf);
    int v = (int)(256.0 * w);
    put((s16)v >> 8);
    put(v);
}

bool Message::changeMsgBuf(int index) {
    if (index == -1) {
        m_cur = m_base;
    } else {
        m_cur = m_bufs[index];
    }
    m_curBuf = m_cur;
    return true;
}

void Message::setDelayPrint(float f1, float f2, float f3, float f4) {
    MsgBuf* buf = m_cur;
    if (f2 == 0.0f) {
        f2 = f1;
    }
    buf->m_rect[0] = (int)(65536.0f * f1);
    buf->m_rect[1] = (int)(65536.0f * f2);
    buf->m_rect[2] = (int)(65536.0f * f3);
    buf->m_rect[3] = (int)(65536.0f * f4);
    buf->m_10 = buf->m_rect[0] * 60 / 2;
    buf->m_1d = 0;
    buf->m_14 = m_cur->m_data;
    buf->m_18[0] = 0;
    buf->m_1c = 0;
}

u8 Message::getTag(char** tagOut) {
    MsgBuf* buf = m_cur;
    u8 r = buf->m_1c;
    buf->m_1c = 0;
    *tagOut = (char*)buf->m_18;
    return r;
}

const u8* Message::advanceDelayPrint(const u8* p) {
    MsgBuf* buf = m_cur;
    int frames = 0;
    buf->m_data[buf->m_pos] = 1;
    for (;;) {
        u8 c = *p;
        if (c < 0x20) {
            switch (c) {
            case 0:
                frames = buf->m_rect[1];
                p++;
                goto parse;
            case 1:
                buf->m_1d = 1;
                return p;
            case 0x17:
                p += 9;
                continue;
            case 0x18:
                p += 3;
                continue;
            case 0x1a:
                p += 2;
                continue;
            case 0x19:
                p += 6;
                continue;
            case 5:
                p += 2;
                continue;
            }
        }
        break;
    }
parse:
    int kind;
    p += MsgParseChar(p, &kind, (u8*)buf->m_18, 0);
    switch (kind) {
    case 0:
        frames = 0;
        break;
    case 1:
        buf->m_1c = 1;
        if (strncmp_((char*)buf->m_18, "\xe3\x83\xbb", 3) == 0) {
            frames = buf->m_rect[2];
        } else if (strncmp_((char*)buf->m_18, "....", 4) == 0) {
            frames = buf->m_rect[3];
        } else {
            frames = buf->m_rect[0];
        }
        break;
    case 2:
        frames = buf->m_rect[1];
        break;
    case 5:
        frames = 0;
        break;
    }
    buf->m_10 += frames * 60;
    return p;
}

u8 Message::isEndDelayPrint() {
    gfApplication* app = g_gfApplication;
    int fps = app->m_frameRate;
    if (fps <= 0) {
        fps = 1;
    }
    MsgBuf* buf = m_cur;
    if (buf->m_rect[0] != 0 && (*(u32*)&app->unkE8[4] >> 27) == 0) {
        buf->m_10 -= 0xe100000 / fps;
        if (buf->m_10 <= 0) {
            buf->m_14 = (u8*)advanceDelayPrint(buf->m_14);
        }
    }
    return buf->m_1d;
}

void Message::init(bool raw, int fontId) {
    if (fontId == 9) {
        if (lbl_805A0178 != 0) {
            SetFontResource(this, 8);
        } else if (lbl_805A0174 != 0) {
            SetFontResource(this, 1);
        } else {
            SetFontResource(this, 2);
        }
    } else {
        SetFontResource(this, fontId);
    }
    SetFlags(0);
    SetEdge(0.0f, nw4r::ut::Color(0xff));
    m_1c0 = 0;
    _84 = 0;
    SetWindowRect(0.0f, 0.0f, 640.0f, 480.0f);
    SetCursor(0.0f, 0.0f, 0.0f);
    SetFixedWidth(32.0f);
    SetScale(1.0f);
    SetParam8C(0.0f);
    SetAlpha(0xff);
    m_1c4 = m_cur->m_cb.m_enable;
    m_1b8 = 0.5f;
    m_1bc = 0.95f;
    if (!raw) {
        GXColor col = {0xff, 0xff, 0xff, 0xff};
        m_1b4 = col;
        SetTextColor(nw4r::ut::Color(col));
        SetupGX();
    }
    *(int*)&m_tagProc.m_data[8] = 0;
    m_tagProc.m_data[4] = 0;
    m_cur->m_data[m_cur->m_pos] = 1;
    GXSetCullMode(GX_CULL_BACK);
}

void ms::CharWriter::SetEdge(float width, nw4r::ut::Color color) {
    m_edgeWidth = width;
    m_edgeColor = color;
}

void Message::printMsgBuf(FontData::FONT_RESOURCE fontId) {
    float textWidth = 0.0f;
    m_unknownFontWidthModifier = 1.0f;
    m_84 = 1.0f;
    init(false, fontId);
    const u8* p = m_cur->m_data;
    while (*p != 1) {
        if (*p < 0x20) {
            switch (*p) {
            case 0:
                p++;
                break;
            case 0x17: {
                s16 a = p[2] + (p[1] << 8);
                s16 b = p[4] + (p[3] << 8);
                s16 cc = p[6] + (p[5] << 8);
                s16 d = p[8] + (p[7] << 8);
                SetWindowRect(a, b, cc, d);
                SetCursor(0.0f, 0.0f, 0.0f);
                p += 9;
                continue;
            }
            case 0x18: {
                u8 a = p[1];
                u8 b = p[2];
                u32 aLow = a & 3;
                u32 bLow = b & 3;
                SetFlags((GetFlags() & ~(((b << 4) & 0x300) + (bLow + ((b << 2) & 0x30)))) | (((a << 4) & 0x300) + (aLow + ((a << 2) & 0x30))));
                if (bLow != 0 && aLow == 0) {
                    SetCursorX(0.0f);
                }
                p += 3;
                continue;
            }
            case 0x1a:
                p += 2;
                switch (p[-1]) {
                case 0:
                    m_1c8();
                    break;
                case 1:
                    m_1cc();
                    break;
                }
                continue;
            case 0x19: {
                u32 color = (p[4] + (p[3] << 8)) + ((p[1] << 24) + (p[2] << 16));
                u8 lineWidth = p[5];
                p += 6;
                float scaleX = 1.0f;
                float scaleY = scaleX;
                float zOff = 0.0f;
                if ((u8)_76[0] != 0) {
                    scaleX = m_scale;
                    zOff = 0.01f;
                    scaleY = -scaleX;
                }
                float bottom = m_rect.bottom;
                float right = m_rect.right;
                float top = m_rect.top;
                float left = m_rect.left;
                drawBoxLine(color, lineWidth, 0, scaleX * left, scaleY * top, scaleX * right, scaleY * bottom, zOff + GetCursorZ());
                SetupGX();
                continue;
            }
            case 5: {
                p += 2;
                int len = MsgParseChar(p, 0, 0, 0);
                if (len != 0) {
                    float r[4];
                    r[0] = 0.0f;
                    r[1] = 0.0f;
                    r[2] = 0.0f;
                    r[3] = 0.0f;
                    GetCharRect(r, p, len);
                    textWidth = r[2] - r[0];
                    if (m_rect.right - m_rect.left < textWidth) {
                        float scale = GetScaleH();
                        float ratio = (m_rect.right - m_rect.left) / textWidth;
                        m_84 = ratio;
                        m_unknownFontWidthModifier = scale * ratio;
                    }
                }
                continue;
            }
            }
        }
        int len = MsgParseChar(p, 0, 0, 0);
        if (len != 0) {
            float r[4];
            r[0] = 0.0f;
            r[1] = 0.0f;
            r[2] = 0.0f;
            r[3] = 0.0f;
            if (textWidth == 0.0f) {
                if ((GetFlags() & 0x100) || (GetFlags() & 0x200) || (GetFlags() & 2) || (GetFlags() & 1)) {
                    GetCharRect(r, p, len);
                    textWidth = r[2] - r[0];
                }
            }
            if (GetFlags() & 2) {
                if (textWidth != 0.0f) {
                    float l = m_rect.left; float r = m_rect.right;
                    float x = (r - l) - textWidth;
                    if (m_84 < 1.0f && x < 0.0f) {
                        x = 0.0f;
                    }
                    SetCursorX(x);
                }
                PrintBytes((const char*)p, len);
            } else if (GetFlags() & 1) {
                if (textWidth != 0.0f) {
                    float l = m_rect.left; float r = m_rect.right;
                    float x = (r - l) - textWidth;
                    if (m_84 < 1.0f && x < 0.0f) {
                        x = 0.0f;
                    }
                    SetCursorX(x * 0.5f);
                }
                PrintBytes((const char*)p, len);
            } else {
                PrintBytes((const char*)p, len);
            }
            p += len;
        }
    }
}

void Message::writeIndexData(void* msgbin, u32 index) {
    MsgBuf* buf = m_cur;
    u32 off = *(u32*)((u8*)msgbin + index * 4);
    u32 next = *(u32*)((u8*)msgbin + (index + 1) * 4);
    int len = next - off;
    memcpy(buf->m_data + buf->m_pos, (char*)msgbin + off, len);
    buf->m_pos += len;
}

void Message::getPrintIndexData(void* msgbin, u32 index, char** outStr, u32* outLen) {
    u32 off = *(u32*)((u8*)msgbin + index * 4);
    u32 next = *(u32*)((u8*)msgbin + (index + 1) * 4);
    *outLen = next - off;
    *outStr = (char*)msgbin + off;
}

void Message::drawBoxLine(s32 color, s32 lineWidth, s32 zTest, float x1, float y1, float x2, float y2, float z) {
    GXSetNumTexGens(0);
    GXSetNumChans(1);
    GXSetNumTevStages(1);
    GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, (GXTevMode)4);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, (GXLogicOp)0xf);
    if (zTest != 0) {
        GXSetZMode(1, GX_ALWAYS, 1);
    }
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    if (lineWidth != 0) {
        ((void (*)(s32, u32))GXSetLineWidth)(lineWidth, 0);
        GXBegin(GX_LINESTRIP, GX_VTXFMT0, 5);
        GXPosition3f32(x1, y1, z);
        GXColor1u32(color);
        GXPosition3f32(x2, y1, z);
        GXColor1u32(color);
        GXPosition3f32(x2, y2, z);
        GXColor1u32(color);
        GXPosition3f32(x1, y2, z);
        GXColor1u32(color);
        GXPosition3f32(x1, y1, z);
        GXColor1u32(color);
    } else {
        GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition3f32(x1, y1, z);
        GXColor1u32(color);
        GXPosition3f32(x2, y1, z);
        GXColor1u32(color);
        GXPosition3f32(x2, y2, z);
        GXColor1u32(color);
        GXPosition3f32(x1, y2, z);
        GXColor1u32(color);
    }
}

static void drawCallbackProjection() {
    GXSetScissor(0, 0, 640, 480);
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    GXSetScissorBoxOffset(0, 0);
    Mtx44 proj;
    float one = 1.0f;
    C_MTXOrtho(proj, 0.0f, 480.0f, 0.0f, 640.0f, 0.0f, one);
    GXSetProjection(proj, GX_ORTHOGRAPHIC);
    Mtx44 mtx;
    PSMTXIdentity((f32(*)[4])mtx);
    GXLoadPosMtxImm((f32(*)[4])mtx, 0);
    GXSetCurrentMtx(0);
}

bool Message::allocMsgBuf(u32 msgSize, u32 numMsgs, Heaps::HeapType heapType) {
    m_bufs = (MsgBuf**)gfHeapManager::alloc(heapType, numMsgs * 4);
    for (int i = 0; i < (int)numMsgs; i++) {
        MsgBuf* buf = new (heapType) MsgBuf(msgSize, heapType);
        buf->m_size = msgSize;
        m_bufs[i] = buf;
    }
    m_numBufs = numMsgs;
    return true;
}

bool Message::attachMsgBuf(u32 index, nw4r::g3d::ScnMdlSimple* scn, const char* nodeName, u8 zCompare, int zUpdate, float scale) {
    msScnObjCallback* prev = *(msScnObjCallback**)((u8*)scn + 0xd4);
    msScnObjCallback* cb = &m_bufs[index]->m_cb;
    if (cb->m_next != NULL) {
        cb->m_next = NULL;
    }
    if (prev != NULL) {
        cb->m_next = prev;
    }
    *(msScnObjCallback**)((u8*)scn + 0xd4) = cb;
    ScnObj_EnableCallbackTiming((nw4r::g3d::ScnObj*)scn, 0x20);
    ScnObj_EnableCallbackExecOp((nw4r::g3d::ScnObj*)scn, 4);
    cb->m_msg = this;
    cb->m_idx = index;
    cb->m_scale = scale;
    cb->m_zCompare = zCompare;
    cb->m_zUpdate = zUpdate;
    cb->m_scnMdl = scn;
    if (*nodeName != 0) {
        nw4r::g3d::ResMdl resMdl = scn->m_resMdl;
        nw4r::g3d::ResNode node = resMdl.GetResNode(nodeName);
        cb->m_nodeId = node.IsValid() ? node->m_nodeIndex : 0;
    } else {
        cb->m_nodeId = 0;
    }
    return true;
}

void Message::detachMsgBuf(nw4r::g3d::ScnMdlSimple* scn) {
    nw4r::g3d::ScnObj* obj = (nw4r::g3d::ScnObj*)scn;
    *(msScnObjCallback**)((u8*)obj + 0xd4) = NULL;
    ScnObj_DisableCallbackTiming(obj, 0x20);
    ScnObj_DisableCallbackExecOp(obj, 4);
}

void Message::setBufField34(int index, int value) {
    m_bufs[index]->m_cb.m_zUpdate = value;
}

void Message::clearMsgBuf() {
    m_cur->m_pos = 0;
    m_cur->m_data[m_cur->m_pos] = 1;
}

void Message::getPrintRect(float* rect, const u8* p) {
    init(true, 9);
    rect[0] = 0.0f;
    rect[2] = 0.0f;
    rect[1] = 0.0f;
    rect[3] = 0.0f;
    MsgBuf* buf = m_cur;
    buf->m_data[buf->m_pos] = 1;
    while (*p != 1) {
        if (*p < 0x20) {
            switch (*p) {
            case 0:
                p++;
                break;
            case 0x17: {
                s16 a = p[2] + (p[1] << 8);
                s16 b = p[4] + (p[3] << 8);
                s16 cc = p[6] + (p[5] << 8);
                s16 d = p[8] + (p[7] << 8);
                SetWindowRect(a, b, cc, d);
                SetCursor(0.0f, 0.0f, 0.0f);
                rect[0] = 0.0f;
                rect[1] = 0.0f;
                rect[2] = (float)(cc - a);
                rect[3] = (float)(d - b);
                p += 9;
                continue;
            }
            case 0x18: {
                u8 a = p[1];
                u8 b = p[2];
                u32 aLow = a & 3;
                u32 bLow = b & 3;
                SetFlags((GetFlags() & ~(((b << 4) & 0x300) + (bLow + ((b << 2) & 0x30)))) | (((a << 4) & 0x300) + (aLow + ((a << 2) & 0x30))));
                if (bLow != 0 && aLow == 0) {
                    SetCursorX(0.0f);
                }
                p += 3;
                continue;
            }
            case 0x1a:
                p += 2;
                continue;
            case 0x19:
                p += 6;
                continue;
            case 5:
                p += 2;
                continue;
            }
        }
        int len = MsgParseChar(p, 0, 0, 0);
        if (len != 0) {
            float r[4];
            r[0] = 0.0f;
            r[1] = 0.0f;
            r[2] = 0.0f;
            r[3] = 0.0f;
            GetCharRect(r, p, len);
            p += len;
            float v0 = r[0];
            rect[0] = (rect[0] > v0) ? v0 : rect[0];
            float v1 = r[1];
            rect[1] = (rect[1] > v1) ? v1 : rect[1];
            float v2 = r[2];
            rect[2] = (rect[2] < v2) ? v2 : rect[2];
            float v3 = r[3];
            rect[3] = (rect[3] < v3) ? v3 : rect[3];
        }
    }
}

void msScnObjCallback::ExecCallback_DRAW_XLU(int pass) {
    if (m_next != NULL) {
        m_next->ExecCallback_DRAW_XLU(pass);
    }
    if (pass == 4) {
        GXSetZMode(1, (GXCompare)m_zUpdate, m_zCompare);
        Message* msg = m_msg;
        msg->_76[0] = 1;
        msg->m_scale = m_scale;
        msg->changeMsgBuf(m_idx);
        Mtx mtx;
        ((nw4r::g3d::ScnMdlSimple*)m_scnMdl)->GetScnMtxPos((nw4r::math::MTX34*)mtx, nw4r::g3d::ScnObj::MTX_VIEW, m_nodeId);
        GXLoadPosMtxImm(mtx, 0);
        GXSetCurrentMtx(0);
        msg->printMsgBuf((FontData::FONT_RESOURCE)9);
        G3DState_Invalidate(0x7ff);
        msg->_76[0] = 0;
    }
}

bool Message::appendSubstr(char* dst, const char* src, int skip, int count) {
    dst += strlen(dst);
    
    while (*src != 0 && skip > 0) {
        if (!(*src & 0x80)) {
            skip--;
            src++;
        } else if ((*src & 0xe0) == 0xc0) {
            skip--;
            src += 2;
        } else if ((*src & 0xf0) == 0xe0) {
            skip--;
            src += 3;
        }
    }
    if (*src == 0) {
        return false;
    }
    while (count > 0) {
        if (!(*src & 0x80)) {
            if (*src == 0) {
                *dst = 0;
                return false;
            }
            *dst = *src;
            dst++;
            count--;
            src++;
        } else if ((*src & 0xe0) == 0xc0) {
            count--;
            *dst++ = *src++;
            *dst++ = *src++;
        } else if ((*src & 0xf0) == 0xe0) {
            count--;
            *dst++ = *src++;
            *dst++ = *src++;
            *dst++ = *src++;
        }
    }
    *dst = 0;
    return true;
}

u32 Message::utf8to16(wchar_t* dst, const char* s) {
    const u8* src = (const u8*)s;
    u32 count = 0;
    while (*src != 0) {
        if (*src <= 0x7f) {
            *dst++ = *src++;
        } else if ((*src >> 5) == 6) {
            *dst++ = ((src[0] & 0x1f) << 6) | (src[1] & 0x3f);
            src += 2;
        } else if ((*src >> 4) == 0xe) {
            *dst++ = ((src[0] & 0xf) << 12) | ((src[1] & 0x3f) << 6) | (src[2] & 0x3f);
            src += 3;
        }
        count++;
    }
    *dst = 0;
    return count;
}

u32 Message::utf16to8(char* dst, const wchar_t* src) {
    u32 count = 0;
    while (*src != 0) {
        if (*src <= 0x7f) {
            *dst = *src;
            dst++;
            src++;
        } else if (*src <= 0x7ff) {
            dst[0] = 0xc0 | ((*src >> 6) & 0x1f);
            dst[1] = 0x80 | (*src & 0x3f);
            src++;
            dst += 2;
        } else {
            dst[0] = 0xe0 | ((*src >> 12) & 0xf);
            dst[1] = 0x80 | ((*src >> 6) & 0x3f);
            dst[2] = 0x80 | (*src & 0x3f);
            src++;
            dst += 3;
        }
        count++;
    }
    *dst = 0;
    return count;
}

char* Message::fullToHalf(char* dst, const char* s) {
    const u8* src = (const u8*)s;
    char* d = dst;
    for (;;) {
        u8 c = *src++;
        if (c == 0xe2) {
            u16 code = src[1] + (src[0] << 8);
            src += 2;
            switch (code) {
            case 0x8098:
                c = 0x27;
                break;
            default:
                src -= 2;
                break;
            }
        } else if (c == 0xef) {
            u16 code = src[1] + (src[0] << 8);
            src += 2;
            switch (code) {
            case 0xbc90:
                c = 0x30;
                break;
            case 0xbc91:
                c = 0x31;
                break;
            case 0xbc92:
                c = 0x32;
                break;
            case 0xbc93:
                c = 0x33;
                break;
            case 0xbc94:
                c = 0x34;
                break;
            case 0xbc95:
                c = 0x35;
                break;
            case 0xbc96:
                c = 0x36;
                break;
            case 0xbc97:
                c = 0x37;
                break;
            case 0xbc98:
                c = 0x38;
                break;
            case 0xbc99:
                c = 0x39;
                break;
            case 0xbca1:
                c = 0x41;
                break;
            case 0xbca2:
                c = 0x42;
                break;
            case 0xbca3:
                c = 0x43;
                break;
            case 0xbca4:
                c = 0x44;
                break;
            case 0xbca5:
                c = 0x45;
                break;
            case 0xbca6:
                c = 0x46;
                break;
            case 0xbca7:
                c = 0x47;
                break;
            case 0xbca8:
                c = 0x48;
                break;
            case 0xbca9:
                c = 0x49;
                break;
            case 0xbcaa:
                c = 0x4a;
                break;
            case 0xbcab:
                c = 0x4b;
                break;
            case 0xbcac:
                c = 0x4c;
                break;
            case 0xbcad:
                c = 0x4d;
                break;
            case 0xbcae:
                c = 0x4e;
                break;
            case 0xbcaf:
                c = 0x4f;
                break;
            case 0xbcb0:
                c = 0x50;
                break;
            case 0xbcb1:
                c = 0x51;
                break;
            case 0xbcb2:
                c = 0x52;
                break;
            case 0xbcb3:
                c = 0x53;
                break;
            case 0xbcb4:
                c = 0x54;
                break;
            case 0xbcb5:
                c = 0x55;
                break;
            case 0xbcb6:
                c = 0x56;
                break;
            case 0xbcb7:
                c = 0x57;
                break;
            case 0xbcb8:
                c = 0x58;
                break;
            case 0xbcb9:
                c = 0x59;
                break;
            case 0xbcba:
                c = 0x5a;
                break;
            case 0xbd81:
                c = 0x61;
                break;
            case 0xbd82:
                c = 0x62;
                break;
            case 0xbd83:
                c = 0x63;
                break;
            case 0xbd84:
                c = 0x64;
                break;
            case 0xbd85:
                c = 0x65;
                break;
            case 0xbd86:
                c = 0x66;
                break;
            case 0xbd87:
                c = 0x67;
                break;
            case 0xbd88:
                c = 0x68;
                break;
            case 0xbd89:
                c = 0x69;
                break;
            case 0xbd8a:
                c = 0x6a;
                break;
            case 0xbd8b:
                c = 0x6b;
                break;
            case 0xbd8c:
                c = 0x6c;
                break;
            case 0xbd8d:
                c = 0x6d;
                break;
            case 0xbd8e:
                c = 0x6e;
                break;
            case 0xbd8f:
                c = 0x6f;
                break;
            case 0xbd90:
                c = 0x70;
                break;
            case 0xbd91:
                c = 0x71;
                break;
            case 0xbd92:
                c = 0x72;
                break;
            case 0xbd93:
                c = 0x73;
                break;
            case 0xbd94:
                c = 0x74;
                break;
            case 0xbd95:
                c = 0x75;
                break;
            case 0xbd96:
                c = 0x76;
                break;
            case 0xbd97:
                c = 0x77;
                break;
            case 0xbd98:
                c = 0x78;
                break;
            case 0xbd99:
                c = 0x79;
                break;
            case 0xbd9a:
                c = 0x7a;
                break;
            default:
                src -= 2;
                break;
            }
        }
        *d++ = c;
        if (*src == 0) break;
    }
    *d = 0;
    return dst;
}

int Message::halfToFull(char* dst, const char* src) {
    const u16 table[94] = { 0xbc81, 0x809c, 0xbc83, 0xbc84, 0xbc85, 0xbc86, 0x8098, 0xbc88, 0xbc89, 0xbc8a, 0xbc8b, 0xbc8c, 0x8892, 0xbc8e, 0xbc8f, 0xbc90, 0xbc91, 0xbc92, 0xbc93, 0xbc94, 0xbc95, 0xbc96, 0xbc97, 0xbc98, 0xbc99, 0xbc9a, 0xbc9b, 0xbc9c, 0xbc9d, 0xbc9e, 0xbc9f, 0xbca0, 0xbca1, 0xbca2, 0xbca3, 0xbca4, 0xbca5, 0xbca6, 0xbca7, 0xbca8, 0xbca9, 0xbcaa, 0xbcab, 0xbcac, 0xbcad, 0xbcae, 0xbcaf, 0xbcb0, 0xbcb1, 0xbcb2, 0xbcb3, 0xbcb4, 0xbcb5, 0xbcb6, 0xbcb7, 0xbcb8, 0xbcb9, 0xbcba, 0xbcbb, 0xbfa5, 0xbcbd, 0xbcbe, 0xbcbf, 0xbd80, 0xbd81, 0xbd82, 0xbd83, 0xbd84, 0xbd85, 0xbd86, 0xbd87, 0xbd88, 0xbd89, 0xbd8a, 0xbd8b, 0xbd8c, 0xbd8d, 0xbd8e, 0xbd8f, 0xbd90, 0xbd91, 0xbd92, 0xbd93, 0xbd94, 0xbd95, 0xbd96, 0xbd97, 0xbd98, 0xbd99, 0xbd9a, 0xbd9b, 0xbd9c, 0xbd9d, 0xbd9e };
    const char* start = src;
    do {
        u8 c = *src;
        if ((s8)c < 0x21 || (s8)c >= 0x7f) {
            *dst++ = c;
        } else {
            u8 lead;
            switch ((s8)c) {
            case 0x27:
            case 0x22:
            case 0x2d:
                lead = 0xe2;
                break;
            default:
                lead = 0xef;
                break;
            }
            u16 code = table[(s8)c - 0x21];
            dst[0] = lead;
            dst[1] = code >> 8;
            dst[2] = code;
            dst += 3;
        }
    } while (*src++ != 0);
    return src - start;
}

int Message::stripTags(const u8* src, int len, int unused, u8* dst) {
    const u8* p = src;
    u8* start = dst;
    u8 tmp[0x5c];
    int k;
    while (*p != 1) {
        if (p - src >= len) {
            break;
        }
        if (*p < 0x20) {
            switch (*p) {
            case 0:
                k = 1;
                while (--k >= 0) {
                    *dst++ = *p++;
                }
                break;
            case 23:
                p += 5;
                break;
            case 26:
                p += 2;
                break;
            case 25:
                p += 6;
                break;
            case 24:
                p += 3;
                break;
            case 5:
                p += 2;
                break;
            case 10:
                k = 1;
                while (--k >= 0) {
                    *dst++ = *p++;
                }
                break;
            case 16:
                k = 3;
                while (--k >= 0) {
                    *dst++ = *p++;
                }
                break;
            case 2:
                p += 2;
                break;
            case 11: {
                int len1;
                int n;
                int len2;
                u8* lenPtr;
                *dst++ = *(volatile u8*)p;
                lenPtr = dst;
                len1 = p[1];
                dst += 2;
                len2 = p[2];
                p += 3;
                n = stripTags(p, len1, 0xffff, tmp);
                lenPtr[0] = n;
                memcpy(dst, tmp, n);
                p += len1;
                dst += n;
                n = stripTags(p, len2, 0xffff, tmp);
                lenPtr[1] = n;
                memcpy(dst, tmp, n);
                p += len2;
                dst += n;
                break;
            }
            case 29:
                p += 2;
                break;
            case 28:
                p += 3;
                break;
            case 18:
                p += 2;
                break;
            case 19:
                p += 1;
                break;
            case 17:
                p += 4;
                break;
            case 7:
                p += 2;
                break;
            case 8:
                p += 2;
                break;
            case 4:
            case 12:
                p += 5;
                break;
            case 3:
                p += 3;
                break;
            case 27:
                p += 2;
                break;
            case 13:
                p += 3;
                break;
            case 14:
                p += 2;
                break;
            case 15:
                p += 3;
                break;
            case 20:
                p += 7;
                break;
            case 22:
                p += 0xd;
                break;
            }
        } else if (!(*p & 0x80)) {
            k = 1;
            while (--k >= 0) {
                *dst++ = *p++;
            }
        } else if ((*p & 0xe0) == 0xc0) {
            k = 2;
            while (--k >= 0) {
                *dst++ = *p++;
            }
        } else if ((*p & 0xf0) == 0xe0) {
            k = 3;
            while (--k >= 0) {
                *dst++ = *p++;
            }
        }
    }
    return dst - start;
}
