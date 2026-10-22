#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <types.h>
#include <ut/ut_stageobject_pool.h>
#include <wn/wn_em_simple.h>

class emWeaponManager : public utStageObjectPool<wnemSimple, 39> {
    char _spacer[0x270];

public:
    virtual ~emWeaponManager();
    virtual void activateObject(wnemSimple* wnem, float, float, int, int, void*, int, Vec3f*, int, int, u8, int, u16);
    virtual void deactivateObject(wnemSimple* wnem);
    virtual void resetProcFncList();
    virtual void resetManageWeaponList();
    wnemSimple* GetManagedWeapon(u32 taskId, u32 p2, u32 p3);
    wnemSimple* GetManagedWeaponFromTaskID(u32 taskId);
    wnemSimple* findWeapon(int taskId, u32 unk1, u32 unk2);

    static void create();
    static void remove();
    static emWeaponManager* getInstance();
};
static_assert(sizeof(emWeaponManager) == 0x298, "Class is wrong size!");
