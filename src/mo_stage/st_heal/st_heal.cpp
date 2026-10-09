#include <revolution/OS/OSError.h>
#include <cm/cm_controller_ai.h>
#include <ef/ef_screen.h>
#include <gf/gf_archive.h>
#include <gm/gm_global.h>
#include <gm/gm_lib.h>
#include <gr/gr_madein.h>
#include <gr/gr_norfair_player_area_check.h>
#include <it/it_manager.h>
#include <memory.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <snd/snd_system.h>
#include <st/st_class_info.h>
#include <st/operator/st_operator_rule.h>
#include <st/st_melee.h>
#include <types.h>
#include <cstdio>

#include <st_heal/st_heal.h>

// MATCH-ONLY: two constructed statics (bss) that every stage TU built with this header set carries; same pair as st_otrain.
struct bss_loc_8_t {
    u32 unk0;
    s32 unk4;
public:
    bss_loc_8_t(s32 p2) {
        unk0 = 0xFF;
        unk4 = p2;
    }
    bss_loc_8_t() { }
};

namespace {
    const bss_loc_8_t bss_loc_8(0);
    const bss_loc_8_t bss_loc_10(1);
}

// MATCH-ONLY: gmPlayerCorpsInitData with the fighter kind as a plain byte (the original reads it with a byte load).
struct stHealCorpsPlayer {
    u8 m_characterKind;
    u8 _01[0x13];
};

// Overlay on the parts of gmGlobalCorps the All-Star rest area reads (names are HYPOTHESIS).
struct stHealCorps {
    u8 _00[0x1C];
    u8 m_figureCount;       // 0x1C: number of defeated fighters to show as figures
    s8 m_remaining;         // 0x1D
    u8 m_heartMask;         // 0x1E: bit n set while heart n has not been taken yet
    u8 m_stageNo;           // 0x1F: round number, selects the "Info_stgNN" sign
    u16 m_extraFigureId;    // 0x20
    u8 _22[2];
    stHealCorpsPlayer m_players[0x24]; // 0x24
};

// TODO: If possible, use a pragma-free alternative that will allocate a
// non-const, 0-valued global variable to .data rather than to .bss
#pragma push
#pragma section ".data" ".data"
__declspec(section ".data") s32 stHeal::data_loc_0 = 0;
#pragma pop

stClassInfoImpl<Stages::Heal, stHeal> stHeal::bss_loc_24;

stHeal* stHeal::create() {
    return new (Heaps::StageInstance) stHeal;
}

stHeal::~stHeal() {
    releaseArchive();
}

bool stHeal::loading() {
    return true;
}

void stHeal::createObj() {
    stHealCorps* corps = (stHealCorps*)g_GameGlobal->m_corps;
    testStageParamInit(m_fileData, 10);
    m_mainGround = grMadein::create(1, "", "", Heaps::StageInstance);
    addGround(m_mainGround);
    m_mainGround->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    m_mainGround->setStageData(m_stageData);
    m_mainGround->initializeEntity();
    m_mainGround->startEntityAutoLoop();
    m_heartNode[0] = m_mainGround->getNodeIndex(0, "heartPosition01");
    m_heartNode[1] = m_mainGround->getNodeIndex(0, "heartPosition02");
    m_heartNode[2] = m_mainGround->getNodeIndex(0, "heartPosition03");
    m_heartNode[3] = m_mainGround->getNodeIndex(0, "heartPosition04");
    m_heartNode[4] = m_mainGround->getNodeIndex(0, "heartPosition05");
    m_warpNode = m_mainGround->getNodeIndex(0, "warpPosition");
    m_itemFigureNode = m_mainGround->getNodeIndex(0, "ItmFigurePosition");
    for (int i = 0; i < 36; i++) {
        char nodeName[0x40];
        sprintf(nodeName, "figurePosition%02d", i + 1);
        m_figureNode[i] = m_mainGround->getNodeIndex(0, nodeName);
    }
    for (int i = 0; i < 19; i++) {
        char nodeName[0x40];
        sprintf(nodeName, "Info_stg%02d", i + 1);
        m_mainGround->setNodeVisibility(i == corps->m_stageNo, 0, nodeName, false, false);
    }
    m_decoGround = grMadein::create(3, "", "", Heaps::StageInstance);
    addGround(m_decoGround);
    m_decoGround->startup(m_fileData, 0, gfSceneRoot::Layer_Effect);
    m_decoGround->setStageData(m_stageData);
    m_decoGround->initializeEntity();
    m_decoGround->startEntityAutoLoop();
    m_effectGround = grMadein::create(4, "", "", Heaps::StageInstance);
    addGround(m_effectGround);
    m_effectGround->startup(m_fileData, 0, gfSceneRoot::Layer_Effect);
    m_effectGround->setStageData(m_stageData);
    m_effectGround->initializeEntity();
    m_effectGround->startEntityAutoLoop();
    m_warpZone = grPlayerAreaCheck::create(2, "grHealWarpZone");
    if (m_warpZone != NULL) {
        addGround(m_warpZone);
        m_warpZone->setArea(0, 0, 8, 3);
        m_warpZone->setGimmickData(&m_warpZone->_playerAreaCheckData);
        m_warpZone->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        m_warpZone->setStageData(m_stageData);
    }
    createCollision(m_fileData, 2, NULL);
    initCameraParam();
    void* posData = m_fileData->getData(Data_Type_Model, 100, 0xFFFE);
    if (posData) {
        nw4r::g3d::ResFile posFile(posData);
        createStagePositions(&posFile);
    } else {
        createStagePositions();
    }
    createWind2ndOnly();
    registScnAnim(static_cast<nw4r::g3d::ResFileData*>(m_fileData->getData(Data_Type_Scene, 0, 0xFFFE)), 0);
    static_cast<grMadein*>(getGround(0))->initializeEntity();
    static_cast<grMadein*>(getGround(0))->startEntityAutoLoop();
    loadStageAttrParam(m_fileData, 30);
    initPosPokeTrainer(1, 0);
    createObjPokeTrainer(m_fileData, 101, "PokeTrainer00", m_pokeTrainerPos, NULL);
    m_timer = data_loc_0;
    m_state = 0;
    *((u8*)g_cmAIController + 0x94) &= ~8; // HYPOTHESIS: clears a camera flag of the AI controller
}

// MSL's qsort (main.dol 0x803F8ACC); the stdlib header of this project does not declare it.
extern "C" void qsort(void* base, u32 num, u32 size, int (*compare)(const void*, const void*));

struct PosSort {
    int m_index;
    int m_value;
    static int compare_int(const void* a, const void* b) {
        return ((const PosSort*)a)->m_value - ((const PosSort*)b)->m_value;
    }
};

namespace {
    s32 data_loc_C8 = 1;
    s32 data_loc_CC = 1;
    s32 data_loc_D0 = 1;
    s32 data_loc_D4 = 1;
    s32 data_loc_D8 = 1;
    s32 data_loc_DC = 2;
}

// The rest area script: hand out the hearts and the figures of the defeated fighters, then wait for a fighter to
// walk into the warp zone.
void stHeal::update(float deltaFrame) {
    stHealCorps* corps = (stHealCorps*)g_GameGlobal->m_corps;
    switch (m_state) {
        case 0:
            m_timer = data_loc_C8;
            m_state = 0xEA;
            // FALL-THROUGH
        case 0xEA:
            m_timer = data_loc_CC;
            m_state = 0xEC;
            break;
        case 0xEC:
            m_timer = data_loc_D0;
            m_state = 0xED;
            break;
        retryHearts:
            m_timer = data_loc_D4;
            m_state = 0xF1;
            break;
        case 0xED:
        case 0xF1: {
            if (!itManager::getInstance()->isCreatableItem(Item_Heart, 1)) {
                goto retryHearts;
            }
            for (int i = 0; i < 5; i++) {
                u32 mask = 1 << i;
                if (corps->m_heartMask & mask) {
                    Matrix mtx(true);
                    if (m_mainGround->getNodeMatrix(&mtx, 0, m_heartNode[i])) {
                        BaseItem* item = itManager::getInstance()->createItem(Item_Heart, 1);
                        if (item != NULL) {
                            Vec3f pos = mtx.getPosition();
                            pos.m_y += 10.0f;
                            item->warp(&pos);
                            item->setVanishMode(false);
                            m_heartItemId[i] = item->m_instanceId;
                        } else {
                            corps->m_heartMask &= ~mask;
                        }
                    }
                }
            }
            PosSort sorted[36];
            for (int i = 0; i < 36; i++) {
                sorted[i].m_index = i;
                Matrix mtx(true);
                if (m_mainGround->getNodeMatrix(&mtx, 0, m_figureNode[i])) {
                    Vec3f pos = mtx.getPosition();
                    sorted[i].m_value = (int)(100.0f * pos.m_z);
                } else {
                    sorted[i].m_value = -10000;
                }
            }
            qsort(sorted, 36, sizeof(PosSort), PosSort::compare_int);
            for (int i = 0; i < 36; i++) {
                sorted[sorted[i].m_index].m_value = i;
            }
            for (int i = 0; i < corps->m_figureCount; i++) {
                Matrix mtx(true);
                if (m_mainGround->getNodeMatrix(&mtx, 0, m_figureNode[i])) {
                    u16 figureId = stOperatorRule::exchangeGmCharacterKind2FigureId((gmCharacterKind)corps->m_players[i].m_characterKind);
                    BaseItem* item = itManager::getInstance()->createItem(Item_Figure, figureId);
                    if (item != NULL) {
                        item->action(1, 1.0f);
                        Vec3f pos = mtx.getPosition();
                        OSReport("PutCorpsFigure%02d:%02d -> %02d  Pos(%f,%f,%f)\n", i, corps->m_players[i].m_characterKind,
                                 (u16)stOperatorRule::exchangeGmCharacterKind2FigureId((gmCharacterKind)corps->m_players[i].m_characterKind),
                                 pos.m_x, pos.m_y, pos.m_z);
                        pos.m_y += 1.0f;
                        item->warp(&pos);
                        item->setVanishMode(false);
                        item->setRenderPriority((u8)sorted[i].m_value);
                    }
                }
            }
            if (corps->m_extraFigureId != 0) {
                Matrix mtx(true);
                if (m_mainGround->getNodeMatrix(&mtx, 0, m_itemFigureNode)) {
                    BaseItem* item = itManager::getInstance()->createItem(Item_Figure, corps->m_extraFigureId);
                    if (item != NULL) {
                        Vec3f pos = mtx.getPosition();
                        pos.m_y += 10.0f;
                        item->warp(&pos);
                        item->setVanishMode(false);
                    }
                }
            }
            Matrix warpMtx(true);
            m_mainGround->getNodeMatrix(&warpMtx, 0, m_warpNode);
            Vec3f warpPos = warpMtx.getPosition();
            m_warpZone->setPos(&warpPos);
            goto checkWarp;
        }
        notWarped:
            m_timer = data_loc_D8;
            m_state = 0x19A;
            break;
        case 0x19A:
            for (int i = 0; i < 5; i++) {
                u32 mask = 1 << i;
                if (corps->m_heartMask & mask) {
                    if (itManager::getInstance()->getItemFromInstanceId(m_heartItemId[i]) == NULL) {
                        corps->m_heartMask &= ~mask;
                    }
                }
            }
            m_isWarped |= m_warpZone->m_playerChecks[0];
            m_isWarped |= m_warpZone->m_playerChecks[1];
        checkWarp:
            if (!m_isWarped) {
                goto notWarped;
            }
            g_sndSystem->playSE(snd_se_AllStar_Heal_Warp, 0, 0x10000, 0, -1);
            GXColor black;
            black.b = 0;
            black.g = 0;
            black.r = 0;
            black.a = 0xFF;
            GXColor fillColor = black;
            efScreen::getInstance()->requestFill(6.0f, 7, 0, &fillColor);
            m_timer = data_loc_DC;
            m_state = 0x1C5;
            break;
        default:
            break;
    }
}

bool stHeal::isEventEnd(int param1, int* eventState, int* eventDecision) {
    *eventState = 6;
    *eventDecision = 5;
    return m_isWarped;
}
