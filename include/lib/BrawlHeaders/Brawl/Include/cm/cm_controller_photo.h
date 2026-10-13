#pragma once

#include <StaticAssert.h>
#include <gf/gf_camera_controller.h>
#include <ut/ut_list.h>

class cmPhotoController : public gfCameraController {
public:
    void addCallBack(utListNode* cb);
    void removeCallBack(utListNode* cb);
    void setFreezeMode(void* p1);
};

class soPhotoController : public cmPhotoController {
public:
    bool setFreezeMode();
};
