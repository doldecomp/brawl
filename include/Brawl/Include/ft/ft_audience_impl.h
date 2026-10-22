#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>
#include <types.h>

class ftAudience {
public:
    virtual ~ftAudience();
    virtual void activate();
    virtual void deactivate();
    virtual void reqHandclapDead(float, bool);
    virtual float correctCheerReaction(float, float);
    virtual void reqCallFgmStopCheer();
    virtual void checkCheer(float, int entryId1, int entryId2);
    virtual bool checkTumultRange(float);
    virtual bool checkTumultLanding(float, float, int entryId);
    virtual bool checkTumultFallSpecial(float, int entryId);
    virtual void checkCheerDefeat(int entryId);
};
static_assert(sizeof(ftAudience) == 4, "Class is wrong size!");

class ftAudienceImpl : public gfTask, public ftAudience {
    char _68[4];
    int m_entryId;
    char _76[4];
    float m_80;
    char _84[44];

public:
    virtual void processFixPosition();
    virtual ~ftAudienceImpl();

    virtual void activate();
    virtual void deactivate();
    virtual void reqHandclapDead(float, bool);
    virtual float correctCheerReaction(float, float);
    virtual void reqCallFgmStopCheer();
    virtual void checkCheer(float, int entryId1, int entryId2);
    virtual bool checkTumultRange(float);
    virtual bool checkTumultLanding(float, float, int entryId);
    virtual bool checkTumultFallSpecial(float, int entryId);
    virtual void checkCheerDefeat(int entryId);
};
static_assert(sizeof(ftAudienceImpl) == 128, "Class is wrong size!");