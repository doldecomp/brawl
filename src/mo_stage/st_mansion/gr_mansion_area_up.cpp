#include <cm/cm_quake.h>
#include <ec/ec_mgr.h>
#include <memory.h>
#include <mt/mt_prng.h>
#include <snd/snd_system.h>

#include <st_mansion/gr_mansion_area_up.h>

grMansionAreaUp* grMansionAreaUp::create(int modelIndex, const char* nodeName, const char* taskName) {
    grMansionAreaUp* ground = new (Heaps::StageInstance) grMansionAreaUp(taskName);
    if (ground != nullptr) {
        ground->setMdlIndex(modelIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grMansionAreaUp::~grMansionAreaUp() { }

void grMansionAreaUp::updateDestroy(float deltaFrame) {
    unk154 -= deltaFrame;
    if (unk154 < 0.0f) {
        unk154 = 0.0f;
    }
    switch (unk150) {
        case State_0:
            setMotion(0, false, true, &unk178);
            setVisibility(true);
            setEnableCollisionStatus(true);
            unk150 = State_2;
            break;
        case State_2:
            setMotionFrame(0.0f, 0);
            if (*unk15C == WorkState_1) {
                setEnableCollisionStatus(false);
                unk150 = State_3;
                unk154 = 10.0f;
            }
            break;
        case State_3:
            setMotionFrame(0.0f, 0);
            if (unk154 == 0.0f) {
                // Stage setup sets TypeLR to 0 or 1 before updates begin.
                u32 effect;
                switch (unk16E) {
                    case TypeLR_0:
                        effect = g_ecMgr->setEffect(ef_ptc_stg_mansion_lucrash);
                        break;
                    case TypeLR_1:
                        effect = g_ecMgr->setEffect(ef_ptc_stg_mansion_rucrash);
                        break;
                }
                g_ecMgr->setParent(effect, m_sceneModels[0], static_cast<u16>(unk170), true);
                float random = randf();
                if (random < 1.0f / 3.0f) {
                    unk17C.playSE(snd_se_stage_Mansion_04, 0, 0, -1);
                } else if (random < 2.0f / 3.0f) {
                    unk17C.playSE(snd_se_stage_Mansion_05, 0, 0, -1);
                } else {
                    unk17C.playSE(snd_se_stage_Mansion_06, 0, 0, -1);
                }
                Vec3f offset(0.0f, 0.0f, 0.0f);
                cmReqQuake(cmQuake::Amplitude_L, &offset);
                unk150 = State_4;
            }
            break;
        case State_4:
            unk178 -= deltaFrame;
            if (unk178 < 0.0f) {
                unk178 = 0.0f;
            }
            if (unk178 == 0.0f) {
                Vec3f offset(0.0f, 1.0f, 0.0f);
                cmReqQuake(cmQuake::Amplitude_L, &offset);
                setVisibility(false);
                *unk15C = WorkState_2;
                g_sndSystem->playSE(snd_se_stage_Mansion_break_finish, 0, 0, 0, -1);
                unk150 = State_5;
            }
            break;
        case State_5:
            if (*unk15C == WorkState_4) {
                setMotion(0, false, true, &unk178);
                setVisibility(true);
                setEnableCollisionStatus(true);
                unk150 = State_6;
            }
            break;
        case State_6:
            setMotionFrame(0.0f, 0);
            if (*unk15C == WorkState_0) {
                unk150 = State_0;
            }
            break;
    }
}
