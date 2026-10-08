#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>

// HYPOTHESIS: source spelling of opaque team return types. The original
// getters return pointers to the embedded team objects, not team numbers.
class soTeam;
class soTeamModule : public soNullable {
public:
    virtual ~soTeamModule();
    virtual soTeam* getTeam() = 0;
    virtual void setTeam(int team, bool notify) = 0;
    virtual soTeam* getHitTeam() = 0;
    virtual soTeam* getIndirectTeam() = 0;
    virtual void setHitTeam(int team) = 0;
    virtual void setTeamOwnerId(int taskId) = 0;
    virtual int getTeamOwnerId() = 0;
    // HYPOTHESIS: uncalled second-team source argument types. Native paths
    // forward one integer register to the corresponding embedded team setter.
    virtual void set2nd(int) = 0;
    virtual void setHit2nd(int) = 0;
    virtual void activate() = 0;
    virtual void deactivate() = 0;
    virtual void reset() = 0;
    // HYPOTHESIS: original bool spelling; native storage is a byte.
    virtual void setEnableOwnerEvent(bool) = 0;
};
static_assert(sizeof(soTeamModule) == 8, "Team interface layout");
