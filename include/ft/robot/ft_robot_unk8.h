#pragma once

#include <types.h>

// HYPOTHESIS: an eight-byte tag object of two words. The original builds two of them as file-local statics, (0xff, 0)
// and (0xff, 1), in every R.O.B. unit that includes the shared item/article headers (ft_robot.cpp and the Gyro status
// unit); nothing reads them. The constructor is the out-of-line function at ft_robot 0xCCF4.
struct ftRobotUnk8 {
    int unk0;
    int unk4;
    ftRobotUnk8(int a, int b);
};
