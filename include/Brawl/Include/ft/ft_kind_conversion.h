#pragma once

#include <StaticAssert.h>
#include <ft/ft_create.h>
#include <gm/gm_lib.h>
#include <types.h>

namespace ftKindConversion {
    u32 convertKind(gmCharacterKind, ftKind* out);
}