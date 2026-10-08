#include <st_greenhill/gr_greenhill.h>
#include <st_greenhill/st_greenhill.h>

// MATCH-ONLY: the stage's float constant pool.
extern const float g_greenhillGuestMotionFrame; // frame at which the guest's cheer starts

// A guest waits until the stage hands it a cheering state (3), plays its sound once its motion is far enough and
// advances its progress until the stage resets it (5).
void grGreenhillGuest::updateActive(float deltaFrame) {
    grGreenhillGuestParam* data = (grGreenhillGuestParam*)getStageData();
    if (data == NULL) {
        return;
    }

    switch (m_state) {
    case 0:
        setMotionLoop(true, 0);
        setVisibility(false);
        m_state = 1;
        // fall through
    case 1:
        if (unk158->unk00 == 3) {
            setVisibility(true);
            m_state = 8;
        }
        break;
    case 8:
        if (unk164 == 0 && getMotionFrame(0) >= g_greenhillGuestMotionFrame) {
            int sound;
            switch (unk158->unk01) {
            case 0:
                sound = 0x1d1b;
                break;
            case 1:
                sound = 0x1d1c;
                break;
            case 2:
                sound = 0x1d1a;
                break;
            default:
                return;
            }
            m_sndGenerator.playSE(static_cast<SndID>(sound), 0, 0, -1);
            unk164 = 1;
        }
        unk158->unk34 += data->unk40;
        if (unk158->unk34 > data->unk44) {
            unk158->unk34 = data->unk44;
        }
        if (unk158->unk00 == 5) {
            unk164 = 0;
            m_state = 0;
        }
        break;
    }
}
