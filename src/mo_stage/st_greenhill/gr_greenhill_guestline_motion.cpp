#include <st_greenhill/gr_greenhill.h>
#include <st_greenhill/gr_greenhill_anim.h>

// MATCH-ONLY: the stage's node name string ("ChrRunNode").
extern const char g_greenhillGuestLineNodeName[];

bool grGreenhillGuestLine::setNode() {
    bool result = grGimmick::setNode();
    getNodeIndex(&m_nodeIndex, 0, g_greenhillGuestLineNodeName);
    return result;
}

// Only animation 0 exists on the run line.
void grGreenhillGuestLine::setMotion(u32 animId, bool shouldLoop, bool force, float* frameCount) {
    grGreenhillSetMotion(this, m_animId, 1, animId, shouldLoop, force, frameCount);
}
