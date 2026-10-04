#pragma once

#include <st_mansion/gr_mansion_area.h>

class grMansionAreaUp : public grMansionArea {
private:
    enum State { // Name unknown
        State_0 = 0,
        State_2 = 2,
        State_3 = 3,
        State_4 = 4,
        State_5 = 5,
        State_6 = 6
    };
    enum WorkState { // Name unknown
        WorkState_0 = 0,
        WorkState_1 = 1,
        WorkState_2 = 2,
        WorkState_4 = 4
    };
    enum TypeLR { // Name unknown
        TypeLR_0 = 0,
        TypeLR_1 = 1
    };

public:
    static grMansionAreaUp* create(int modelIndex, const char* nodeName, const char* taskName);
    grMansionAreaUp(const char* taskName) : grMansionArea(taskName) { }
    virtual ~grMansionAreaUp();
    virtual void updateDestroy(float deltaFrame);
};
