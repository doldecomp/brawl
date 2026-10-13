#pragma once

#include <StaticAssert.h>
#include <gf/gf_error_manager.h>
#include <gf/gf_file_io.h>
#include <types.h>

class gfErrorCheckCallback : public gfFileIO::ErrorCallback {
    u16 unk8;
public:
    virtual ~gfErrorCheckCallback() { }
    virtual void userProc() {
        u32 p1 = 4;
        switch (static_cast<s32>(unk8)) {
            case -4:
                p1 = 5;
                break;
            case -9:
                p1 = 6;
                break;
            case -11:
                p1 = 7;
                break;
            default:
                break;
        }
        gfErrorManager::getInstance()->notifyError(p1, 0);
    }
};
static_assert(sizeof(gfErrorCheckCallback) == 0xC, "Class is the wrong size!");

class gfErrorCheck {
public:
    static void init();
    static void check();
};
static_assert(sizeof(gfErrorCheck) == 0x1, "Class is the wrong size!");
