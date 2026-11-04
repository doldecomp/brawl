#include <memory.h>
#include <mt/mt_prng.h>

#include <st_gw/gr_gw_scene.h>

namespace {

enum State { // Name unknown
    State_0 = 0,
    State_1 = 1,
    State_2 = 2,
    State_3 = 3,
    State_4 = 4,
};

// Only the stage-data prefix read by this unit is described.
struct StageData { // Name unknown
    u8 unk00[0x2C];
    float unk2C;
};

}

grGWScene* grGWScene::create(int modelIndex, const char* nodeName, const char* taskName) {
    grGWScene* ground = new (Heaps::StageInstance) grGWScene(taskName);
    if (ground != nullptr) {
        ground->setMdlIndex(modelIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grGWScene::grGWScene(const char* taskName) : grGW(taskName) {
    unk174 = 0;
    unk178 = 0.0f;
    unk17C = nullptr;
    unk180 = nullptr;
    unk184 = nullptr;
    unk188 = nullptr;
    unk18C = 1;
    unk18D = 0;
    unk190 = nullptr;
}

grGWScene::~grGWScene() { }

void grGWScene::update(float deltaFrame) {
    grGW::update(deltaFrame);
    StageData* data = static_cast<StageData*>(getStageData());
    if (data == nullptr) {
        return;
    }
    unk154 -= deltaFrame;
    if (unk154 < 0.0f) {
        unk154 = 0.0f;
    }
    switch (unk150) {
        case State_0:
            setMotion(0, false, true, &unk164);
            setMotionFrame(unk164, 0);
            setVisibility(false);
            setEnableCollisionStatus(false);
            clearStep();
            if (unk15C != 0) {
                unk18C = 0;
            }
            unk174 = 0;
            unk178 = 0.0f;
            unk150 = State_1;
            break;
        case State_1:
            if (*unk158 == unk15C) {
                if (unk18C == 1) {
                    setMotion(1, false, true, nullptr);
                    unk18C = 0;
                    unk160 = 0.0f;
                } else {
                    setMotion(0, true, true, &unk164);
                    setMotionFrame(unk164, 0);
                    unk160 = unk164;
                    m_motionRatio *= -1.0f;
                }
                selectStep();
                if (randf() < data->unk2C) {
                    unk18D = 1;
                }
                unk150 = State_3;
            }
            break;
        case State_2:
            break;
        case State_3:
            if (*unk158 != unk15C) {
                if (unk184 != nullptr) {
                    ++*unk184;
                }
                setMotion(0, false, true, &unk164);
                if (m_motionRatio < 0.0f) {
                    m_motionRatio *= -1.0f;
                }
                updateSubEnd(deltaFrame);
                unk18D = 0;
                unk150 = State_4;
            } else {
                if (getMotionFrame(0) > unk160) {
                    setMotion(1, false, false, nullptr);
                } else {
                    unk160 = getMotionFrame(0);
                }
                setVisibility(true);
                setEnableCollisionStatus(true);
                updateSub(deltaFrame);
            }
            break;
        case State_4:
            if (getMotionFrame(0) >= unk164) {
                unk150 = State_0;
            }
            break;
    }
}

void grGWScene::clearStep() { }

void grGWScene::selectStep() { }

void grGWScene::updateSub(float deltaFrame) {
    updateStep(deltaFrame);
    updateEvent(deltaFrame);
}

void grGWScene::updateSubEnd(float deltaFrame) { }

void grGWScene::updateStep(float deltaFrame) { }

void grGWScene::updateEvent(float deltaFrame) { }
