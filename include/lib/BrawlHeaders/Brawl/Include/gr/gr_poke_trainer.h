#pragma once

#include <StaticAssert.h>
#include <gr/gr_yakumono.h>
#include <types.h>

class grPokeTrainer : public grYakumono {
protected:
    Vec3f* m_posWork;
    Vec3f* m_posDstWork;
    int m_nNode;
    int m_eNode;

public:
    grPokeTrainer(const char* taskName);
    virtual void processAnim();
    virtual void update(float deltaFrame);
    virtual bool setNode();
    virtual void updateCallback(float deltaFrame);
    virtual void setPosWork(Vec3f*);
    virtual void setPosDstWork(Vec3f*);
    virtual ~grPokeTrainer();

};
static_assert(sizeof(grPokeTrainer) == 0x160, "Class is wrong size!");