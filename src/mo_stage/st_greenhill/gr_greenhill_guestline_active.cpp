#include <st_greenhill/gr_greenhill.h>
#include <st_greenhill/st_greenhill.h>

// The run line waits for the stage to start the guests (state 3), plays its animation at the guests' pace and
// tells the stage it is done (5) when the animation reaches its end frame.
void grGreenhillGuestLine::updateActive(float deltaFrame) {
    switch (m_state) {
    case 0:
        setMotion(1, false, true, NULL);
        setVisibility(false);
        m_state = 1;
        // fall through
    case 1:
        if (unk158->unk00 == 3) {
            setMotion(0, false, true, &m_motionEndFrame);
            setVisibility(true);
            m_state = 8;
        }
        break;
    case 8:
        m_motionRatio = unk158->unk34;
        if (getMotionFrame(0) >= m_motionEndFrame) {
            unk158->unk00 = 5;
            m_state = 0;
        }
        break;
    }
}
