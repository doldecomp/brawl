#include <gf/gf_copyefb.h>
#include <gf/gf_keep_fb.h>
#include <gf/gf_3d_scene.h>
#include <revolution/GX/GXPixel.h>
#include <revolution/GX/GXTypes.h>

void gfKeepFrameBuffer::update() {
    if (m_isActive && m_needsUpdate) {
        gfCopyEFBMgr::getInstance()->getEFB(0);
        m_needsUpdate = false;
    }
}

void gfKeepFrameBuffer::render() {
    if (m_isActive) {
        GXSetZMode(false, GX_ALWAYS, false);
        GXColor black;
        black.r = 0;
        black.g = 0;
        black.b = 0;
        black.a = 0xFF;
        gfCopyEFBMgr::getInstance()->drawCopyEFB(0, &black);
    }
}

void gfKeepFrameBuffer::startKeepScreen() {
    m_isActive = true;
    m_needsUpdate = true;
    g_gfSceneRoot->setUseCopyFB(0);
}

void gfKeepFrameBuffer::endKeepScreen() {
    m_isActive = false;
    g_gfSceneRoot->setUseCopyFB(1);
}
