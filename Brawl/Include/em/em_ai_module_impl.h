#pragma once

#include <StaticAssert.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/collision/so_collision_attack_event_presenter.h>
#include <types.h>

struct emAIInfo {
    u8 unk0[0x4];
    s32 unk4;
};
// TODO size assertion

class emAIModuleImpl : public soAnimCmdEventObserver, public soCollisionAttackEventObserver {
public:
    emAIInfo* getCurrentAIInfo();
};
static_assert(sizeof(emAIModuleImpl) == 0x18, "Class is wrong size!");
// TODO fix size assertion
