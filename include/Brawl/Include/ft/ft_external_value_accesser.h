#pragma once

#include <StaticAssert.h>
#include <ft/fighter.h>
#include <types.h>

namespace ftExternalValueAccesser {
    float getWeight(Fighter* fighter);
    Vec3f getHipPos(Fighter* fighter);
}