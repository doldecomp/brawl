#pragma once

#include <StaticAssert.h>
#include <mt/mt_vector.h>
#include <so/controller/so_controller_module_impl.h>
#include <so/stageobject.h>
#include <types.h>

class soExternalValueAccesser {
public:
    static int getTeamNo(StageObject* stageObject);
    static Vec3f getPos(StageObject* stageObject);
    static float getLr(StageObject* stageObject);
    static SituationKind getSituationKind(StageObject* stageObject);
    static int getStatusKind(StageObject* stageObject);
    static bool getWorkFlag(StageObject* stageObject, u32);
    static int getWorkInt(StageObject* stageObject, u32);
    static soModuleAccesser* getModuleAccesser(StageObject* stageObject);
    static soCollisionHitModule* getCollisionHitModule(StageObject* stageObject);
    static soControllerModule* getControllerModule(StageObject* stageObject);
    static u32 getTeamOwnerId(StageObject* stageObject);
};
// TODO size assertion
