#include <gf/gf_decomp.h>
#include <gf/gf_heap_manager.h>
#include <gf/gf_error_manager.h>
#include <gf/gf_pad_system.h>
#include <gf/gf_shutdown_manager.h>
#include <gm/gm_global.h>
#include <ms/ms_message.h>
#include <ms/ms_resfont.h>
#include <nw4r/ut/ut_Color.h>
#include <nw4r/ut/ut_ResFont.h>
#include <revolution/GX.h>
#include <revolution/CX/CXCompression.h>
#include <snd/snd_system.h>
#include <sr/sr_common.h>
#include <types.h>

// TODO: These belong to different files

// Big compressed object, possibly linked from an independent data-only unit
// .data start:0x80423980 end:0x8042ADD0
extern CXStream g_LZEncodedAlertFont;

// global defined in ms_resfont.cpp
extern nw4r::ut::ResFont g_AlertFont;

// probably defined in gf_file_io.cpp
extern const char* g_ErrorMsgTable[12];

static gfErrorManager* g_gfErrorManager;

gfErrorManager* gfErrorManager::getInstance() {
    if (!g_gfErrorManager)
        g_gfErrorManager = new (Heaps::SystemFW) gfErrorManager;
    return g_gfErrorManager;
}

gfErrorManager* gfErrorManager::create() {
    g_gfErrorManager = new (Heaps::SystemFW) gfErrorManager;
    return g_gfErrorManager;
}

gfErrorManager::gfErrorManager() :
    m_isFatal(false),
    m_isSuspended(false),
    m_unused(false),
    m_isMoviePaused(false),
    m_msgBgColor(nw4r::ut::Color::WHITE),
    m_msgTextColor(nw4r::ut::Color::WHITE)
{
    m_errorCode = 0;
    m_reasonCode = 0;
    m_msgScreen = new (Heaps::SystemFW) Message(0x400, Heaps::SystemFW);

    m_msgBgColor.Set(0xDE, 0xF3, 0xD7, 0xFF);
    m_msgTextColor.Set(0x8B, 0xB6, 0x7D, 0xFF);

    gfDecomp dec(gfHeapManager::getHeap(Heaps::GameGlobal));
    dec.decomp(&g_LZEncodedAlertFont, 0x741E);
    m_fontData = dec.m_decompData;
    FontData::loadAlertFont(m_fontData);
}

void gfErrorManager::update() {
    if (m_isSuspended) {
        if (m_updateDone == 0) {
            g_gfPadSystem->stopMotorAllForce();
            g_gfHomeMenu->setBan(1, 4);
        }
        m_updateDone++;
    }
}

void gfErrorManager::renderPre() {
    Message* msg = m_msgScreen;
    Message::drawBoxLine(m_msgBgColor, 0, 0, 0.0f, 0.0f, 640.0f, 480.0f, 0.0f);
    msg->SetFont(g_AlertFont);
    msg->changeMsgBuf(-1);
    msg->clearMsgBuf();
    msg->setFace(7);
    msg->setFixedWidth(-1.0);
    if (true == g_GameGlobal->getGlobalRecordMenuDatap()->m_isWidescreen)
        msg->setScale(0.65f, 0.845f);
    else
        msg->setScale(0.65f);
    msg->setCallProjection(0);
    msg->setWindow(20.0f, 100.0f, 620.0f, 380.0f);
    msg->setDrawFlag(0x101, 0x303);
    msg->setColor(m_msgTextColor);
    const char* msgText = g_ErrorMsgTable[m_errorCode];
    if (0 == m_reasonCode)
        msg->printf(msgText);
    else {
        msg->printf(msgText);
        msg->printf("\n\n%d", m_reasonCode);
    }
}

void gfErrorManager::render() {
    Message* msg = m_msgScreen;
    GXColor white;
    white.b = 255;
    white.a = 255;
    white.g = 255;
    white.r = 255;
    GXSetFog(GX_FOG_NONE, white, 0.0f, 1000.0f, 1.0f, 1000.0f);
    GXSetNumTevStages(1);
    GXSetNumIndStages(0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, false, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, 60, false, 125);
    GXSetZCompLoc(true);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
    GXSetZMode(false, GX_ALWAYS, false);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
    msg->printMsgBuf(FontData::FONT_ALERT);
}

void gfErrorManager::notifyError(u32 errorCode, u32 reasonCode) {
    bool statusChanged;
    suspendGame(statusChanged, errorCode);
    if (statusChanged) {
        m_reasonCode = reasonCode;
        m_errorCode = errorCode;
    }
    if (!isRecoverable(m_errorCode)) {
        m_isFatal = true;
        g_gfShutdownManager.unkC = 0;
    }
}

void gfErrorManager::notifyErrorRecovery(bool skip) {
    if (m_isSuspended && !m_isFatal && !skip && isRecoverable(m_errorCode)) {
        m_isSuspended = false;
        m_updateDone = 0;
        g_gfHomeMenu->setBan(0, 4);
        if (mvMoviePlayer::getInstance()) {
            if (!m_isMoviePaused)
                mvMoviePlayer::getInstance()->resetPause();
            m_isMoviePaused = false;
        }
        if (g_sndSystem)
            g_sndSystem->specialResume();
        if (g_gfHomeMenu)
            g_gfHomeMenu->start();
    }
}
