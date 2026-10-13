#pragma once

#include <StaticAssert.h>
#include <st/st_common_gimmick.h>
#include <types.h>

class stCollisionWork {
    grCollData::VtxData* m_vtxDatas;
    grCollData::LineData* m_lineDatas;
    grCollData::JointData* m_jointDatas;
public:
    u16 m_vtxLen;
    bool m_isClosed;
    char _0xf;

    void initialize();
};
static_assert(sizeof(stCollisionWork) == 0x10, "Class is wrong size!");

class stMelee : public stCommonGimmick {
protected:
    // 0
    char _spacer[0x10];

    stTrigger* m_wind2ndTrigger; // +0x1C4

    grGimmickWindData2nd* m_wind2ndData; // +0x1C8

    // 0x18
    char _396[0xc];

public:
    stMelee(char const* name, srStageKind stageKind);
    virtual void processBegin();
    virtual void processUpdate();
    virtual void getItemGenPac(gfArchive** archive);
    virtual void getFighterStartPos(Vec3f* startPos, int fighterIndex);
    virtual void getFighterReStartPos(Vec3f* startPos, int fighterIndex);
    virtual bool createWind2ndOnly();
    virtual grGimmickWindData2nd* getWind2ndOnlyData() { return m_wind2ndData; }
    virtual void updateWind2ndOnly();
    virtual bool isReStartSamePoint() { return true; }
    virtual void update(float deltaFrame);
    virtual void setCameraLimitRange(float unk1, float unk2, float unk3, float unk4); // TODO
    virtual void resetCameraLimitRange();                                             // TODO
    virtual bool checkChangeScene();                                                  // TODO
    virtual void resetChangeScene();                                                  // TODO
    virtual void setChangeSceneNumber(s32 n);                                         // TODO
    ~stMelee();

    void zoomInCamera();
    void zoomOutCamera(float, float);
    void setPlayerPositionIndexSerial();
    int playSeBasic(SndID id, float p2);
    void stopSeBasic(int index, float);
    void setSePan(int index, float);
    void setGravityHalf();
    void setGravityNormal();
    grCollision* createCollisionSelf(stCollisionWork* collisionWork, Ground* ground, const char*, const char*, u16);

    static bool getPlayerPosition(int playerNo, Vec3f* pos);
};
static_assert(sizeof(stMelee) == 472, "Class is wrong size!");
