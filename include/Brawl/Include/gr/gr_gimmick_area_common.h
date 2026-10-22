#pragma once

#include <StaticAssert.h>
#include <gr/gr_yakumono.h>
#include <types.h>

class grGimmickAreaCommon : public grYakumono {
protected:
    stGimmickAreaData* m_gimmickAreaData;
    soAreaData m_areaData;
    soSet<soAreaData> m_areaDataSet;
    ykAreaData m_ykData;

public:
    grGimmickAreaCommon(const char* taskName);
    virtual void update(float deltaFrame);
    virtual void startup(gfArchive* archive, u32 unk1, gfSceneRoot::LayerType layerType);
    virtual void onGimmickEvent(soGimmickEventArgs* eventInfo, int* taskId);
    virtual ~grGimmickAreaCommon();

};
static_assert(sizeof(grGimmickAreaCommon) == 0x188, "Class is wrong size!");