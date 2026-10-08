#pragma once

#include <types.h>

class soModuleAccesser;

// Translates between the ability id Kirby currently wears and the id of the fighter it was copied from; fighters that
// Kirby can copy ask it which of their moves they are playing.
class ftKirbyCopyAbilityIdConverter {
public:
    // HYPOTHESIS: argument meanings.
    int convCorrectToOrigId(int unk, int statusKind, soModuleAccesser* moduleAccesser, bool unk2);
};
extern ftKirbyCopyAbilityIdConverter g_ftKirbyCopyAbilityIdConverter;
