#pragma once

#include <GX/GXTypes.h>
#include <memory.h>
#include <types.h>
#include <gf/gf_archive.h>
#include <gm/gm_lib.h>
#include <gr/gr_madein.h>
#include <gr/gr_tengan_event.h>
#include <mt/mt_prng.h>
#include <mt/mt_vector.h>
#include <nw4r/ut/ut_Color.h>
#include <snd/snd_id.h>
#include <st/se_util.h>
#include <st/stage.h>
#include <st/st_class_info.h>
#include <st/st_melee.h>

ST_CLASS_INFO

class stEmblem : public stMelee {
    grTenganEvent m_scene_lifecycle;
    grTenganEvent event2;
    grTenganEvent m_curr_scene_effect;
    grTenganEvent event4;
    grTenganEvent m_curr_scene;
    grTenganEvent eventArray[2];
    u32 m_effects[14];
    s32 m_scene_ground_num[0x5];
    grMadein* m_scene_grounds[0x5];
    bool m_change_scene;
    bool m_not_first_scene;//: 1;
    s32 m_scene_num;
    s32 m_prev_scene_num;
    float unk6f8;
    u32 unk6fc[2];
    u32 unk704[2];
    u32 m_unused;
    s32 unk710;
    s32 ambientSnd;
    float unk718;
    float unk71C;
    float unk720;
    float unk724;
    s32 unkSnd728;
    float rockTimer;
    float rockFixTime;
    grCollision* unk734;
    grCollision* unk738;
    u8 m_isKemuriHigh;
    float m_lampEffTimer;
    u32 unk744;
    s32 quakeSnd;
    u8 m_eventType;
    StSeUtil::SeSeqInstance<2, 2> m_se_player;
    StSeUtil::SeSeqInstance<2, 2> m_se_player2;
    u8 unk800;
    float unk804;
    float unk808;
    //s32 m_great_fox_engine_se;
    //snd3DGenerator m_great_fox_sndgen;
    //snd3DGenerator m_pleiades_sndgen;
    //Vec3f m_slope_rotate;
    //u8 m_corneria_phase;

    static const int SCENE_ASTEROID = 0;
    static const int SCENE_BATTLESHIP = 1;
    static const int SCENE_CORNERIA = 2;
    static const int SCENE_SPACE = 3;

    void setSceneCollision();
    grMadein* createSceneGround(s16 index);
    void moveGround(float param3,bool isStartHigh, Vec3f* pos);
    void startScene();
    void updateScene(float deltaFrame);
    void updateScene00(float deltaFrame);
    void updateScene01(float deltaFrame);
    void updateScene02(float deltaFrame);
    void startAppearCore();
public:
    stEmblem();

    virtual ~stEmblem();
    virtual void createObj();
    virtual bool loading();
    virtual void update(float deltaFrame);
    virtual void updateSE(float deltaFrame);
    virtual bool checkChangeScene();
    virtual void resetChangeScene();
    virtual void setChangeSceneNumber(s32 n);

    virtual bool isEventEnd(int param1, int* eventState, int* decision);
    virtual GXColor getFinalTechniqColor();

    static stEmblem* create();
    static stClassInfoImpl<Stages::Emblem, stEmblem> bss_loc_14;
};

StSeUtil::UnkStruct data_loc_0[] = {
    {snd_se_stage_Emblem_sutatue_break, 0.000, 0.000, 0.000},
    {snd_se_stage_Emblem_floor_break, 0.000, 67.000, 0.000}
};

StSeUtil::UnkStruct data_loc_20[] = {
    {snd_se_stage_Emblem_sutatue_break, 0.000, 0.000, 0.000},
    {snd_se_stage_Emblem_floor_break, 0.000, 36.000, 0.000}
};

StSeUtil::UnkStruct data_loc_40[] = {
    {snd_se_stage_Emblem_under_amb, 0.000, 0.000, 0.000},
};

SndID data_loc_11A0[] = {
    snd_se_stage_Emblem_sutatue_break,
    snd_se_stage_Emblem_floor_break
};

static const size_t SndSeqTable1Size = sizeof(data_loc_0)/sizeof(data_loc_0[0]);
static const size_t SndSeqTable2Size = sizeof(data_loc_40)/sizeof(data_loc_40[0]);
//static const size_t SndSeqTable3Size = sizeof(data_loc_980)/sizeof(data_loc_980[0]);
//static const size_t SndSeqTable4Size = sizeof(data_loc_9C0)/sizeof(data_loc_9C0[0]);
static const size_t SndIDTableSize = sizeof(data_loc_11A0)/sizeof(data_loc_11A0[0]);
