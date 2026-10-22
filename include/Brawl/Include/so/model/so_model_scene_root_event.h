#pragma once

#include <gf/gf_3d_scene_event.h>
#include <types.h>

class soModelSceneRootEvent : public gfSceneRootEvent {
public:
    virtual void notify(s32 p1);
};
// TODO size assertion
