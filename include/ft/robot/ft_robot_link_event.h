#pragma once

#include <so/link/so_link_event_presenter.h>

// Link events R.O.B. sends to the articles he owns (gyro, gyro holder, Diffusion Beam). HYPOTHESIS names: 0x838-0x83d
// are the gyro/final-beam state notifications, 0x839 doubles as the volley event of the Final Smash.
struct ftRobotGyroLinkEvent : soLinkEventArgs {
    ftRobotGyroLinkEvent(int kind) : soLinkEventArgs(kind) { }
};
