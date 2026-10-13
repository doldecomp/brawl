#pragma once

#include <StaticAssert.h>
#include <ft/ft_audience_impl.h>
#include <types.h>

class ftAudienceNull : public ftAudience {
public:
    virtual ~ftAudienceNull();
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
static_assert(sizeof(ftAudienceNull) == 4, "Class is wrong size!");

class ftAudienceManager {
public:
    ftAudienceImpl* m_audienceImpl;
    ftAudienceNull* m_audienceNull;
    ftAudience* m_audience;
};
static_assert(sizeof(ftAudienceManager) == 12, "Class is wrong size!");

extern ftAudienceManager* g_ftAudienceManager;