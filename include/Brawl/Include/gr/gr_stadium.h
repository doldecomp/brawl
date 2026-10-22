#pragma once

#include <StaticAssert.h>
#include <gr/gr_yakumono.h>

class grStadium : public grYakumono {
protected:
    float m_0x110;
    float m_scaleY;
    float m_0x118;
public:
    grStadium(const char* taskName);
    virtual void update(float deltaFrame);
    virtual void updateCallback(u32 index);
    virtual void setScaleY(float scaleY);
    virtual float getScaleY();
    virtual ~grStadium();

};
static_assert(sizeof(grStadium) == 348, "Class is wrong size!");