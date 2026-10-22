#pragma once
#include <StaticAssert.h>
#include <gf/gf_task.h>
#include <nw4r/g3d/g3d_scngroup.h>
class MenuRoot : public gfTask {
public:
    char spacer[0x08];
    nw4r::g3d::ScnGroup* scene;

    static MenuRoot* create(const char* name, int, const char* cameraPath);
};
