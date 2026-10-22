#pragma once

#include <StaticAssert.h>
#include <gf/gf_scene.h>
#include <mu/mu_menu_controller.h>
#include <mu/selchar/mu_selchar.h>
#include <types.h>

class scSelChar : public gfScene {
public:
    muMenuController m_menuControllers[5];
    char _0x350[0xB0];
    muSelCharTask* m_selCharMenu;
    char _0x404[0x18];

    virtual void start();
    virtual s32 process();
    virtual s32 exit();
    virtual void setModule();
    virtual ~scSelChar();
};
static_assert(sizeof(scSelChar) == 0x41c, "Class is wrong size!");
