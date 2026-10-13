#pragma once

#include <StaticAssert.h>
#include <nw4r/snd/snd_Sound3DActor.h>
#include <snd/snd_id.h>
#include <types.h>

class snd3DGenerator {
    nw4r::snd::Sound3DActor* m_sndActor;

public:
    snd3DGenerator();
    virtual ~snd3DGenerator();

    s32 playSE(SndID sndID, int unk, int unk2, int unk4);
    s32 prepareSE(SndID p1, s32 p2);
    void startSE(s32 p1, s32 p2);
    void setPos(Vec3f* pos);
    void stopSE(s32 p1, s32 p2);
};
