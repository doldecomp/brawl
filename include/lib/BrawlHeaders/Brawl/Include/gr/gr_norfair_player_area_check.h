#pragma once

#include <StaticAssert.h>
#include <gr/gr_gimmick_area_common.h>
#include <types.h>

struct grPlayerAreaCheckData {
public:
    stGimmickAreaData m_areaData;
    char _0x28[4];
};
static_assert(sizeof(grPlayerAreaCheckData) == 0x2C, "Class is wrong size!");

class grPlayerAreaCheck : public grGimmickAreaCommon {
protected:
    grPlayerAreaCheckData _playerAreaCheckData;
    grPlayerAreaCheckData* m_playerAreaCheckData;
    char _0x1b8[0x28];
    int m_0x1E0;
    int m_0x1E4;
    char _0x1E8[4];
    bool m_playerChecks[4];

public:
    inline grPlayerAreaCheck(const char* taskName) : grGimmickAreaCommon(taskName) {
        m_0x1E0 = 0;
        m_0x1E4 = 0;
        this->makeCalcuCallback(1, Heaps::StageInstance);
        this->setCalcuCallbackRoot(3);
        m_playerChecks[0] = 0;
        m_playerChecks[1] = 0;
        m_playerChecks[2] = 0;
        m_playerChecks[3] = 0;
    };
    virtual void update(float deltaFrame);
    virtual void startup(gfArchive* archive, u32 unk1, gfSceneRoot::LayerType layerType);
    virtual void onGimmickEvent(soGimmickEventArgs* eventInfo, int* taskId);
    virtual ~grPlayerAreaCheck();

    void setArea(int posX, int posY, int rangeX, int rangeY);

    static grPlayerAreaCheck* create(int mdlIndex, const char* taskName);

};
static_assert(sizeof(grPlayerAreaCheck) == 0x1f0, "Class is wrong size!");