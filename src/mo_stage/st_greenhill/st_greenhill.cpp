#include <gf/gf_archive.h>
#include <memory.h>
#include <mt/mt_prng.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <nw4r/ut/ut_algorithm.h>
#include <st_greenhill/gr_greenhill.h>

#include <st_greenhill/st_greenhill.h>

enum GuestEventState {
    GuestEvent_Initialize,
    GuestEvent_Wait,
    GuestEvent_WaitForSingle,
    GuestEvent_SelectOrder,
    GuestEvent_DispatchOrder,
    GuestEvent_ResetDelay
};

enum GuestState {
    Guest_Start = 3,
    Guest_Inactive = 5
};

stClassInfoImpl<Stages::GreenHill, stGreenhill> stGreenhill::bss_loc_14;

stGreenhill* stGreenhill::create() {
    return new (Heaps::StageInstance) stGreenhill;
}

stGreenhill::stGreenhill() : stMelee("stGreenhill", Stages::GreenHill) {
    unk1D8[0] = 5;
    unk1D8[1] = 5;
    unk1D8[2] = 5;
    unk1DB = 0;
    unk1DC = 0;
    unk1DD = 0;
    unk1DE = GuestEvent_Initialize;
    unk1E0 = 0.0f;
    unk1E4 = 0;
    memset(unk1E5, 0, sizeof(unk1E5));
    for (u8 i = 0; i < 3; i++) {
        unk1E8[i].unk00 = Guest_Inactive;
        unk1E8[i].unk01 = 3;
        unk1E8[i].unk04.setIdentity();
        unk1E8[i].unk34 = 1.0f;
    }
    unk2C0 = 5;
    memset(unk290, 0, sizeof(unk290));
}

stGreenhill::~stGreenhill() {
    releaseArchive();
}

bool stGreenhill::loading() {
    return true;
}

void stGreenhill::createObj() {
    testStageParamInit(m_fileData, 10);
    testStageDataInit(m_fileData, 20, 80);
    createBackground();
    createBreaks();
    createMarker();
    createGuests();
    createCollision(m_fileData, 2, nullptr);
    initCameraParam();
    nw4r::g3d::ResFile posData(m_fileData->getData(Data_Type_Model, 100, 0xFFFE));
    if (posData.ptr()) {
        nw4r::g3d::ResFile copyPosData = posData;
        createStagePositions(&copyPosData);
    } else {
        createStagePositions();
    }
    createWind2ndOnly();
    loadStageAttrParam(m_fileData, 30);
    registScnAnim(static_cast<nw4r::g3d::ResFileData*>(m_fileData->getData(Data_Type_Scene, 0, 0xFFFE)), 0);
    initPosPokeTrainer(1, 0);
    createObjPokeTrainer(m_fileData, 101, "PokeTrainer00", m_pokeTrainerPos, nullptr);
}

void stGreenhill::createBackground() {
    grGreenhillBg* ground = grGreenhillBg::create(1, "StgGreenhillMain", "grGreenhillMainBg");
    if (ground) {
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->setPositions(unk290);
        ground->setState(&unk1DB);
    }
}

void stGreenhill::createBreaks() {
    grGreenhillBreak* ground = grGreenhillBreak::create(2, "StgGreenhillBrk_gake01", "grGreenhillBreak01");
    if (!ground) {
        return;
    }
    addGround(ground);
    ground->setIndex(0);
    ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground->setStageData(m_stageData);
    ground->setState(&unk1D8[0]);
    ground->setBackgroundState(&unk1DB);
    ground = grGreenhillBreak::create(3, "StgGreenhillBrk_gake02", "grGreenhillBreak02");
    if (!ground) {
        return;
    }
    addGround(ground);
    ground->setIndex(1);
    ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground->setStageData(m_stageData);
    ground->setState(&unk1D8[1]);
    ground->setBackgroundState(&unk1DB);
    ground = grGreenhillBreak::create(4, "StgGreenhillBrk_gake03", "grGreenhillBreak03");
    if (!ground) {
        return;
    }
    addGround(ground);
    ground->setIndex(2);
    ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground->setStageData(m_stageData);
    ground->setState(&unk1D8[2]);
    ground->setBackgroundState(&unk1DB);
}

void stGreenhill::createMarker() {
    grGreenhillCheck* ground = grGreenhillCheck::create(5, "StgGreenhillMarker", "grGreenhillMarker");
    if (ground) {
        addGround(ground);
        ground->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
        ground->setStageData(m_stageData);
        ground->setState(&unk2C0);
        ground->setBreakStates(unk1D8);
        ground->setPositions(unk290);
    }
}

void stGreenhill::createGuests() {
    unk1E8[0].unk01 = 0;
    unk1E8[1].unk01 = 1;
    unk1E8[2].unk01 = 2;
    grGreenhillGuest* ground1 = grGreenhillGuest::create(10, "StgGreenhillKnuckles_TopN", "grGreenhillKnuckles");
    if (!ground1) {
        return;
    }
    addGround(ground1);
    ground1->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground1->setStageData(m_stageData);
    ground1->setGuestData(&unk1E8[0]);
    grGreenhillGuest* ground2 = grGreenhillGuest::create(11, "StgGreenhillSilver_TopN", "grGreenhillSilver");
    if (!ground2) {
        return;
    }
    addGround(ground2);
    ground2->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground2->setStageData(m_stageData);
    ground2->setGuestData(&unk1E8[1]);
    grGreenhillGuest* ground3 = grGreenhillGuest::create(12, "StgGreenhillTails_TopN", "grGreenhillTails");
    if (!ground3) {
        return;
    }
    addGround(ground3);
    ground3->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground3->setStageData(m_stageData);
    ground3->setGuestData(&unk1E8[2]);
    grGreenhillGuestLine* ground4 =
        grGreenhillGuestLine::create(13, "StgGreenhillRunPosition", "grGreenhillGuestLineN");
    if (!ground4) {
        return;
    }
    addGround(ground4);
    ground4->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground4->setStageData(m_stageData);
    ground4->setGuestData(&unk1E8[0]);
    grGreenhillGuestLine* ground5 =
        grGreenhillGuestLine::create(13, "StgGreenhillRunPosition", "grGreenhillGuestLineS");
    if (!ground5) {
        return;
    }
    addGround(ground5);
    ground5->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground5->setStageData(m_stageData);
    ground5->setGuestData(&unk1E8[1]);
    grGreenhillGuestLine* ground6 =
        grGreenhillGuestLine::create(13, "StgGreenhillRunPosition", "grGreenhillGuestLineT");
    if (!ground6) {
        return;
    }
    addGround(ground6);
    ground6->startup(m_fileData, 0, gfSceneRoot::Layer_Ground);
    ground6->setStageData(m_stageData);
    ground6->setGuestData(&unk1E8[2]);
}

void stGreenhill::update(float deltaFrame) {
    if (m_isDevil == true) {
        setCameraLimitRange(-160.0f, 180.0f, 140.0f, -45.0f);
    } else {
        resetCameraLimitRange();
    }
    updateGuests(deltaFrame);
}

struct GreenhillStageData {
    u8 unk00[0x34];
    float unk34;
    float unk38;
    float unk3C;
    u8 unk40[8];
    float unk48;
    u32 unk4C;
};

void stGreenhill::updateGuests(float deltaFrame) {
    GreenhillStageData* data = static_cast<GreenhillStageData*>(m_stageData);
    if (!data) {
        return;
    }
    unk1E0 -= deltaFrame;
    if (unk1E0 < 0.0f) {
        unk1E0 = 0.0f;
    }
    switch (unk1DE) {
        case GuestEvent_Initialize:
            unk1E0 = data->unk34;
            unk1DE = GuestEvent_Wait;
            // FALL-THROUGH
        case GuestEvent_Wait:
            if (unk1E0 == 0.0f) {
                if (unk1E4 >= data->unk4C) {
                    unk1E4 = 0;
                    unk1DE = GuestEvent_SelectOrder;
                } else if (randf() < data->unk48) {
                    unk1E4 = 0;
                    unk1DE = GuestEvent_SelectOrder;
                } else {
                    u8 index = 3.0f * randf();
                    index = nw4r::ut::Min<u8>(2, nw4r::ut::Max<u8>(0, index));
                    unk1E8[index].unk00 = Guest_Start;
                    unk1E8[index].unk34 = 0.5f + 0.3f * randf();
                    unk1E4++;
                    unk1DE = GuestEvent_WaitForSingle;
                }
            }
            break;
        case GuestEvent_WaitForSingle:
            if (unk1E8[0].unk00 == Guest_Inactive && unk1E8[1].unk00 == Guest_Inactive &&
                unk1E8[2].unk00 == Guest_Inactive) {
                unk1DE = GuestEvent_ResetDelay;
            }
            break;
        case GuestEvent_SelectOrder:
            if (randf() < 1.0f / 3.0f) {
                unk1E5[0] = 0;
                if (randf() < 0.5f) {
                    unk1E5[1] = 1;
                    unk1E5[2] = 2;
                } else {
                    unk1E5[1] = 2;
                    unk1E5[2] = 1;
                }
            } else if (randf() < 2.0f / 3.0f) {
                unk1E5[0] = 1;
                if (randf() < 0.5f) {
                    unk1E5[1] = 0;
                    unk1E5[2] = 2;
                } else {
                    unk1E5[1] = 2;
                    unk1E5[2] = 0;
                }
            } else {
                unk1E5[0] = 2;
                if (randf() < 0.5f) {
                    unk1E5[1] = 0;
                    unk1E5[2] = 1;
                } else {
                    unk1E5[1] = 1;
                    unk1E5[2] = 0;
                }
            }
            unk1DE = GuestEvent_DispatchOrder;
            unk1E0 = 15.0f;
            // FALL-THROUGH
        case GuestEvent_DispatchOrder:
            if (unk1E0 == 0.0f) {
                if (unk1E5[0] == 0xFF) {
                    if (unk1E8[0].unk00 == Guest_Inactive && unk1E8[1].unk00 == Guest_Inactive &&
                        unk1E8[2].unk00 == Guest_Inactive) {
                        unk1DE = GuestEvent_ResetDelay;
                    }
                } else {
                    unk1E8[unk1E5[0]].unk00 = Guest_Start;
                    unk1E5[0] = unk1E5[1];
                    unk1E5[1] = unk1E5[2];
                    unk1E5[2] = 0xFF;
                    unk1E0 = 24.0f + 21.0f * randf();
                }
            }
            break;
        case GuestEvent_ResetDelay:
            unk1E0 = data->unk38 + (data->unk3C - data->unk38) * randf();
            unk1DE = GuestEvent_Wait;
            break;
    }
}
