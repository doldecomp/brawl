#pragma once

#include <StaticAssert.h>
#include <types.h>
#include <ft/fighter.h>
#include <so/article/so_article.h>
#include <ft/ft_log.h>

struct ftOwnerData {
    char _[0x838];
    ftLog m_log;
};
static_assert(sizeof(ftOwnerData) == 0xd44, "Class is wrong size!");

class ftOwner {
    ftOwnerData* m_data;
    void* m_input;
    short _8;
    u8 _10;
    u8 _11;

public:
    virtual ~ftOwner();
    virtual bool isSubOwner();
    virtual void setDamage(float damage, bool);
    virtual float getDamage();
    virtual void setStartDamage(float startDamage);
    virtual float getStartDamage();
    virtual float getHitPoint();
    virtual void setBeatCount(int playerIndex, int beatCount);
    virtual u32 getCheerDefeatFrame();
    virtual void setSuicideCount(short suicideCount);
    virtual void setLogFloat(float, u32 index1, u32 index2);
    virtual void addLogFloat(float, u32 index1, u32 index2);
    virtual void setLogInt(int, u32 index1, u32 index2);
    virtual void addLogInt(int, u32 index1, u32 index2);
    virtual void setLogFlag(bool, u32 index1, u32 index2);
    virtual void onLogFlag(u32 index1, u32 index2);
    virtual void offLogFlag(u32 index1, u32 index2);
    virtual void setLogActionInfo(ftLogActionInfo);
    virtual void addAttackInfo(const soLogAttackInfo&);
    virtual void addAttackPattern(const soLogAttackInfo&);

    void setTeam(int team);
    void setPointTeam(int pointTeam);
    int setDeadCount(int deadCount);
    int getDeadCount();
    void addLostCoin(int numCoinsToAdd);
    int getCoin();
    float getCoinDropRate();
    void addCoin(int numCoinsToAdd);
    int getBeatCount(int playerIndex);
    int getSuicideCount();
    int getStockCount();
    float getHitPointMax();
    void setMetal(bool);
    void setFinal(bool, bool);
    void setRabbitCap(bool);
    void setReflector(bool);
    void setFlower(bool);
    void setCurry(bool);
    void setInfiniteScaling(Fighter::Scaling::Kind, Fighter::Scaling::Type);
    void setHitPointMax(float);
    void setSlipMul(float);
    void setSlipInterval(bool);
    void setResultWinRotY(float);

    inline ftLog& getLog() const { return m_data->m_log; };
};
static_assert(sizeof(ftOwner) == 16, "Class is wrong size!");