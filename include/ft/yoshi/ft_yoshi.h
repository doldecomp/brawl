#pragma once
#include <ft/fighter.h>
// Only the inherited interface is needed by status callbacks. The constructor's
// 0x222B0 allocation establishes the opaque remainder of this fighter.
class ftYoshi : public Fighter {
    u8 unk194[0x222b0 - sizeof(Fighter)];
public:
    void createGuardColorAnim();
    void deleteGuardColorAnim();
    void updateGuardColorAnim();
};
static_assert(sizeof(ftYoshi) == 0x222b0, "Yoshi allocation size is wrong!");
