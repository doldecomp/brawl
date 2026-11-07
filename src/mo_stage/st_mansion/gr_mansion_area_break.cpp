#include <memory.h>

#include <st_mansion/gr_mansion_area_break.h>

grMansionAreaBreak* grMansionAreaBreak::create(int modelIndex, const char* nodeName, const char* taskName) {
    grMansionAreaBreak* ground = new (Heaps::StageInstance) grMansionAreaBreak(taskName);
    if (ground != nullptr) {
        ground->setMdlIndex(modelIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grMansionAreaBreak::~grMansionAreaBreak() { }

void grMansionAreaBreak::updateDestroy(float deltaFrame) {
    unk154 -= deltaFrame;
    if (unk154 < 0.0f) {
        unk154 = 0.0f;
    }
    switch (unk150) {
        case State_0:
            setVisibility(false);
            unk150 = State_2;
            break;
        case State_2:
            if (*unk15C == WorkState_2) {
                switch (unk16D) {
                    case Type_3:
                        setVisibility(false);
                        break;
                    case Type_2:
                        setVisibility(true);
                        break;
                }
                unk150 = State_4;
            }
            break;
        case State_4:
            if (*unk15C == WorkState_3) {
                switch (unk16D) {
                    case Type_3:
                        setVisibility(true);
                        break;
                    case Type_2:
                        setVisibility(false);
                        break;
                }
            } else if (*unk15C == WorkState_2) {
                switch (unk16D) {
                    case Type_2:
                        switch (*unk160) {
                            case SubState_1:
                            case SubState_2:
                            case SubState_3:
                                break;
                            default:
                                setMotionFrame(0.0f, 0);
                                break;
                        }
                        break;
                }
            } else if (*unk15C == WorkState_4) {
                // The original explicitly leaves this state unchanged.
            } else if (*unk15C == WorkState_0) {
                unk150 = State_0;
            }
            break;
    }
}
