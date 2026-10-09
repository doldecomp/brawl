#include <memory.h>
#include <nw4r/g3d/g3d_scnmdl.h>
#include <nw4r/math/math_arithmetic.h>
#include <gf/gf_3d_scene.h>

#include <st_battle/gr_battlefield.h>

grBattleField* grBattleField::create(int mdlIndex, const char* tgtNodeName, const char* taskName) {
    grBattleField* ground = new (Heaps::StageInstance) grBattleField(taskName);
    if (ground) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(tgtNodeName);
    }
    return ground;
}

grBattleField::~grBattleField() { }

// Fades the alpha of the stage's shadow plane ("MShadow1") with the day/night cycle: invisible during the first and
// last 400 frames' worth of dusk/dawn, fully visible in between.
void grBattleField::update(float deltaFrame) {
    if (m_isUpdate) {
        if (m_shadowMatIndex == 0) {
            nw4r::g3d::ResMdl resMdl;
            nw4r::g3d::ScnMdl* scnMdl = m_sceneModels[0];
            if (scnMdl == NULL) {
                return;
            }
            resMdl = scnMdl->m_resMdl;
            if (!resMdl.IsValid()) {
                return;
            }
            u32 matCount = resMdl.GetResMatNumEntries();
            u32 i = 0;
            for (; i != matCount; i++) {
                nw4r::g3d::ResMat resMat = resMdl.GetResMat("MShadow1");
                if (resMat.IsValid()) {
                    m_shadowMatIndex = resMat->m_id;
                    break;
                }
            }
            if (i == matCount) {
                m_shadowMatIndex = 0xFF;
            }
        }
        if (m_shadowMatIndex != 0xFF) {
            float frame = 0.0f;
            if (g_gfSceneRoot->m_anmScnRes != NULL) {
                frame = g_gfSceneRoot->m_anmScnRes->GetFrame();
            }
            float alpha;
            if (frame >= 5600.0f && frame <= 6000.0f) {
                alpha = (6000.0f - frame) / 400.0f;
                alpha = nw4r::math::FSelect(alpha - 0.0f, alpha, 0.0f);
                alpha = nw4r::math::FSelect(alpha - 1.0f, 1.0f, alpha);
            } else if (frame >= 400.0f && frame <= 5600.0f) {
                alpha = 1.0f;
            } else if (frame >= 0.0f && frame <= 400.0f) {
                alpha = frame / 400.0f;
                alpha = nw4r::math::FSelect(alpha - 0.0f, alpha, 0.0f);
                alpha = nw4r::math::FSelect(alpha - 1.0f, 1.0f, alpha);
            } else {
                alpha = 0.0f;
            }
            nw4r::g3d::ResMdl resMdl;
            nw4r::g3d::ResMat resMat;
            nw4r::g3d::ResMatTevColor copyTev;
            nw4r::g3d::ResMatTevColor baseTev;
            GXColor baseColor = {0xFF, 0xFF, 0xFF, 0xFF};
            GXColor copyColor = {0xFF, 0xFF, 0xFF, 0xFF};
            nw4r::g3d::ScnMdl* scnMdl = m_sceneModels[0];
            if (scnMdl != NULL) {
                resMdl = scnMdl->m_resMdl;
                if (resMdl.IsValid()) {
                    resMat = resMdl.GetResMat(m_shadowMatIndex);
                    if (resMat.IsValid()) {
                        nw4r::g3d::ScnMdl::CopiedMatAccess access(scnMdl, resMat->m_id);
                        copyTev = access.GetResMatTevColor(false);
                        if (copyTev.IsValid()) {
                            baseTev = resMat.GetResMatTevColor();
                            if (baseTev.IsValid()) {
                                baseTev.GXGetTevColor(GX_TEVREG0, &baseColor);
                                copyTev.GXGetTevColor(GX_TEVREG0, &copyColor);
                                copyColor.a = (u8)((float)baseColor.a * alpha);
                                copyTev.GXSetTevColor(GX_TEVREG0, copyColor);
                                copyTev.DCStore(false);
                                resMat.DCStore(false);
                            }
                        }
                    }
                }
            }
        }
    }
}
