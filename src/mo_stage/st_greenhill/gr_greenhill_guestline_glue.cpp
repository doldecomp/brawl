#include <st_greenhill/gr_greenhill.h>
#include <st_greenhill/st_greenhill.h>

// MATCH-ONLY: the stage's float constant pool.
extern const float g_greenhillGuestLineMotionEnd;

inline grGreenhillGuestLine::grGreenhillGuestLine(const char* taskName) : grGreenhill(taskName) {
    unk158 = NULL;
    m_nodeIndex = 0;
    m_animId = 1;
    m_motionEndFrame = g_greenhillGuestLineMotionEnd;
}

grGreenhillGuestLine* grGreenhillGuestLine::create(int mdlIndex, const char* nodeName, const char* taskName) {
    grGreenhillGuestLine* ground = new (Heaps::StageInstance) grGreenhillGuestLine(taskName);
    if (ground != NULL) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grGreenhillGuestLine::~grGreenhillGuestLine() {
}

// The guests' matrices follow the run line node.
void grGreenhillGuestLine::processAnim() {
    Ground::processAnim();
    if (unk158 != NULL) {
        getNodeMatrix(&unk158->unk04, 0, m_nodeIndex);
    }
}

void grGreenhillGuestLine::update(float deltaFrame) {
    grGimmick::update(deltaFrame);
    if (m_isUpdate) {
        updateActive(deltaFrame);
    }
}
