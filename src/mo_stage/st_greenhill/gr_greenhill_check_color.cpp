#include <st_greenhill/gr_greenhill.h>
#include <nw4r/g3d/g3d_scnmdl.h>

// MATCH-ONLY: keep the original constants and the material name string.
extern const GXColor g_greenhillCheckColorA; // 0x00, 0x50, 0x80, 0xFF
extern const GXColor g_greenhillCheckColorB; // 0x80, 0x00, 0x00, 0xFF
extern const char g_greenhillCheckMarkerBallMaterial[]; // "markerBall"

// Tints the ball's marker material: state 0 blue, state 1 red.
void grGreenhillCheck::changeColor(int state) {
    nw4r::g3d::ResMdl resMdl;
    nw4r::g3d::ResMat resMat;
    nw4r::g3d::ResMatTevColor tevColor;
    nw4r::g3d::ScnMdl* scnMdl = m_sceneModels[0];
    if (scnMdl != NULL) {
        resMdl = scnMdl->m_resMdl;
        if (resMdl.IsValid()) {
            resMat = resMdl.GetResMat(g_greenhillCheckMarkerBallMaterial);
            if (resMat.IsValid()) {
                nw4r::g3d::ScnMdl::CopiedMatAccess access(scnMdl, resMat->m_id);
                tevColor = access.GetResMatTevColor(false);
                if (tevColor.IsValid()) {
                    GXColor color;
                    switch (state) {
                    case 0: {
                        GXColor colorA = g_greenhillCheckColorA;
                        color = colorA;
                        break;
                    }
                    case 1: {
                        GXColor colorB = g_greenhillCheckColorB;
                        color = colorB;
                        break;
                    }
                    }
                    tevColor.GXSetTevColor(GX_TEVREG0, color);
                    tevColor.DCStore(false);
                    resMat.DCStore(false);
                }
            }
        }
    }
}
