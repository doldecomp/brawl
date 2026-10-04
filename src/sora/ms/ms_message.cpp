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

int Message::writeTagClear(u8* dst) {
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

void Message::clearMsgBuf() {
    m_cur->m_pos = 0;
    m_cur->m_data[m_cur->m_pos] = 1;
}

static void drawCallbackProjection() {}
