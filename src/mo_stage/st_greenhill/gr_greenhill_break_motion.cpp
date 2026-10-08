#include <st_greenhill/gr_greenhill.h>
#include <st_greenhill/gr_greenhill_anim.h>

// Only animation 0 exists on the breakable pieces.
void grGreenhillBreak::setMotion(u32 animId, bool shouldLoop, bool force, float* frameCount) {
    grGreenhillSetMotion(this, m_animId, 1, animId, shouldLoop, force, frameCount);
}
