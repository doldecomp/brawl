#pragma once

#include <st_mansion/gr_mansion_area.h>

class grMansionAreaBreak : public grMansionArea {
private:
    enum State { // Name unknown
        State_0 = 0,
        State_2 = 2,
        State_4 = 4
    };
    enum WorkState { // Name unknown
        WorkState_0 = 0,
        WorkState_2 = 2,
        WorkState_3 = 3,
        WorkState_4 = 4
    };
    enum Type { // Name unknown
        Type_2 = 2,
        Type_3 = 3
    };
    enum SubState { // Name unknown
        SubState_1 = 1,
        SubState_2 = 2,
        SubState_3 = 3
    };

public:
    static grMansionAreaBreak* create(int modelIndex, const char* nodeName, const char* taskName);
    grMansionAreaBreak(const char* taskName) : grMansionArea(taskName) { }
    virtual ~grMansionAreaBreak();
    virtual void updateDestroy(float deltaFrame);
};
