#include <st_greenhill/gr_greenhill.h>

// MATCH-ONLY: the stage's node name strings ("DanmenBrk02", "DanmenBrk03", "DanmenBrk01", then one per piece type).
extern const char g_greenhillBreakNodeNames[][12];

// Looks up the node the hit boxes of this piece are attached to.
bool grGreenhillBreak::setNode() {
    const char (*names)[12] = g_greenhillBreakNodeNames;
    bool result = grGimmick::setNode();
    switch (m_type) {
    case 0:
        getNodeIndex(&unk184, 0, names[3]);
        break;
    case 1:
        getNodeIndex(&unk184, 0, names[4]);
        break;
    case 2:
        getNodeIndex(&unk184, 0, names[5]);
        break;
    }
    return result;
}
