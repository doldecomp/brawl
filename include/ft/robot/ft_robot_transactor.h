#pragma once

#include <ft/ft_transactor.h>
#include <types.h>

class soArticle;
class soModuleAccesser;
class wnRobotBeam;

// R.O.B.'s per-fighter helper: keeps the chest lamp effect in sync with the Robo Beam charge and starts the beam
// article. The same code serves Kirby when he copies the move.
class ftRobotTransactor : public ftTransactor {
public:
    ftRobotTransactor();
    virtual ~ftRobotTransactor();
    virtual void init(soModuleAccesser* moduleAccesser);
    virtual void exit(soModuleAccesser* moduleAccesser);
    virtual void processUpdate(soModuleAccesser* moduleAccesser);
    virtual void processFixPosition(soModuleAccesser* moduleAccesser);
    virtual bool activeArticle(soArticle* article, soModuleAccesser* moduleAccesser);
    // Local declaration of the REL singleton-holder entry point.
    static ftRobotTransactor* getInstance();
    void initTransact(soModuleAccesser* moduleAccesser);
    void processUpdateSpecialNTransact(soModuleAccesser* moduleAccesser);
    void processUpdateEffectTransact(soModuleAccesser* moduleAccesser);
    bool activeArticle1(wnRobotBeam* weapon, soModuleAccesser* acc, u32 resourceId);
    int getLampEffectKind(float charge, soModuleAccesser* moduleAccesser) __attribute__((never_inline));
};
static_assert(sizeof(ftRobotTransactor) == 4, "Transactor singleton layout is wrong!");
