#pragma once

#include <StaticAssert.h>
#include <em/em_create.h>
#include <gf/gf_archive.h>
#include <types.h>

class emArchive {
public:
    emArchive(gfArchive* param, gfArchive* brres, gfArchive* enmCommon, gfArchive* primFaceBrres, EnemyKind enemyKind);
    ~emArchive();
    bool isComp() const;
    void remove();
    u32 getWeaponResourceId() const;

private:
    u32 enmCommonResourceId;
    u32 brresResourceId;
    u32 paramResourceId;
    u32 weaponResourceId;
    u32 faceTexBrresResourceId;
    u32 extendBrresResourceId;
};
static_assert(sizeof(emArchive) == 24, "Class is wrong size!");
