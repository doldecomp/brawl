#pragma once

#include <ac/ac_anim_cmd_impl.h>
#include <so/so_module_accesser.h>

class soEffectScreen {
public:
    void notifyEventAnimCmd(const acAnimCmd* cmd, soModuleAccesser* accessor);
};
