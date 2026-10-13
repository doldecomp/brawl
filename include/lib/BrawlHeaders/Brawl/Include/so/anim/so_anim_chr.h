#pragma once

#include <StaticAssert.h>
#include <nw4r/g3d/g3d_anmchr.h>
#include <types.h>

class soAnimChr {
    nw4r::g3d::AnmObjChrRes* m_anmChrRes;
    float m_animFrame;
    float m_startFrame;
    float m_saveFrame;
    float m_rate;
    float m_frameAhead;
    u8 m_loopFlag: 1;
    u8 m_reverseFlag: 1;

    void reinit(bool destroy);
public:
    soAnimChr();
    ~soAnimChr();
    void reset();
    void relinquishAnimObj();
    void updateFrame(float p1);
    void setFrame(float p1);
    bool isEnd() const;
    bool isLooped() const;
    void setAnimObj(float p1, float p2, nw4r::g3d::AnmObjChrRes *p3, u8 p4, u8 p5);
    void destroyAnimObj();
    void disableNode(u32 id);
    float getEndFrame(nw4r::g3d::AnmObjChrRes* p1) const;
    void rewind();
    void turnBack();
};
static_assert(sizeof(soAnimChr) == 0x1C, "Class is the wrong size!");
