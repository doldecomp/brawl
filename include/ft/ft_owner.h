#pragma once

// Local shadow of BrawlHeaders' ft/ft_owner.h: the original, plus the start position/direction setters the fighter manager calls.

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
public:
    u8 unkA; // cleared by ftManager::gameSet
private:
    u8 _11;

public:
    bool getSpycloak() const; // HYPOTHESIS: the player wears the Spycloak (hides R.O.B.'s chest lamp)
    virtual ~ftOwner();
    virtual bool isSubOwner();
    virtual void setDamage(float damage, bool);
    virtual float getDamage();
    virtual void setStartDamage(float startDamage);
    virtual float getStartDamage();
    virtual float getHitPoint();
    virtual void setBeatCount(int playerIndex, int beatCount);
    virtual u32 getCheerDefeatFrame();
    virtual void setSuicideCount(u16 suicideCount);
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

    void setStartPos(Vec3f* pos);
    void setOperationCpu(bool isCpu);
    void setStartLr(float lr);
    void setTeam(int team);
    void setPointTeam(int pointTeam);
    int setDeadCount(int deadCount);
    void setStockCount(int stockCount);
    int getDeadCount();
    void addLostCoin(int numCoinsToAdd);
    int getCoin();
    float getCoinDropRate();
    void addCoin(int numCoinsToAdd);
    void setPickupCoin(int coins);
    int getPickupCoin();
    void addGenerateCoin(int coins);
    int getBeatCount(int playerIndex);
    int getBeatCountTotal();
    void process();
    void setController(int kind, u64* buttons0, u64* buttons1);
    bool sameCheckController(int kind, u64* buttons0, u64* buttons1);
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