#pragma once

#include <mt/mt_vector.h>
#include <st_mansion/gr_mansion.h>

class grMansionGround : public grMansion {
private:
    Vec3f* unk158;

public:
    static grMansionGround* create(int modelIndex, const char* nodeName, const char* taskName);
    grMansionGround(const char* taskName) : grMansion(taskName), unk158(nullptr) { }
    virtual ~grMansionGround();
    virtual void processAnim();
    virtual void setPosGimmickWork(Vec3f* positions) { unk158 = positions; }
};
static_assert(sizeof(grMansionGround) == 0x15C, "Class is wrong size!");
