#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <types.h>

class soParamCustomizeModule : soNullable {
public:
    virtual ~soParamCustomizeModule() { }
    virtual void activate() = 0;
    virtual void setDefault() = 0;
    virtual void addCustomize(u8) = 0;
    virtual void removeCustomize(u8) = 0;
    virtual bool isCustomize(u32) const = 0;
    virtual float getAttackPowerMul(void* p1) = 0; // TODO type, see ftLucarioParamCustomizeModule
    virtual void setAttackPowerMulPattern(float) = 0;
    virtual float getAttackPowerMulPattern() = 0;
    virtual void setAttackPowerMulScale(float) = 0;
    virtual float getAttackPowerMulScale() = 0;
    virtual float getAttackPowerMulArticle() = 0;
    virtual float getAttackReactionMul() = 0;
    virtual float getWalkSpeedMul() = 0;
    virtual int getParamInt(u32, u32) = 0;
    virtual float getParamFloat(u32, u32) = 0;
    virtual void* getParamIndefinite(u32, u32) = 0;
};
static_assert(sizeof(soParamCustomizeModule) == 8, "Class is wrong size!");

class soParamCustomizeModuleImpl : soParamCustomizeModule {
    float m_attackPowerMulPattern;
    float m_attackPowerMulScale;

public:
    virtual ~soParamCustomizeModuleImpl();
    virtual void activate();
    virtual void setDefault();
    virtual void addCustomize(u8);
    virtual void removeCustomize(u8);
    virtual bool isCustomize(u32) const;
    virtual float getAttackPowerMul(void* p1);
    virtual void setAttackPowerMulPattern(float pattern) {
        m_attackPowerMulPattern = pattern;
    }

    virtual float getAttackPowerMulPattern() {
        return m_attackPowerMulPattern;
    }

    virtual void setAttackPowerMulScale(float scale) {
        m_attackPowerMulScale = scale;
    }

    virtual float getAttackPowerMulScale() {
        return m_attackPowerMulScale;
    }
    virtual float getAttackPowerMulArticle();
    virtual float getAttackReactionMul();
    virtual float getWalkSpeedMul();
    virtual int getParamInt(u32, u32);
    virtual float getParamFloat(u32, u32);
    virtual void* getParamIndefinite(u32, u32);
};
static_assert(sizeof(soParamCustomizeModuleImpl) == 16, "Class is wrong size!");

class soParamCustomizeModuleNull : soParamCustomizeModule {
public:
    virtual ~soParamCustomizeModuleNull() { }
    virtual void activate() { }
    virtual void setDefault() { }
    virtual void addCustomize(u8) { }
    virtual void removeCustomize(u8) { }
    virtual bool isCustomize(u32) const { return false; }
    virtual float getAttackPowerMul(void* p1) { return 1.0f; }
    virtual void setAttackPowerMulPattern(float) { }
    virtual float getAttackPowerMulPattern() { return 1.0f; }
    virtual void setAttackPowerMulScale(float) { }
    virtual float getAttackPowerMulScale() { return 1.0f; }
    virtual float getAttackPowerMulArticle() { return 1.0f; }
    virtual float getAttackReactionMul() { return 1.0f; }
    virtual float getWalkSpeedMul() { return 1.0f; }
    virtual int getParamInt(u32, u32) { return 0; }
    virtual float getParamFloat(u32, u32) { return 0.0f; }
    virtual void* getParamIndefinite(u32, u32) { return nullptr; }
};
static_assert(sizeof(soParamCustomizeModuleNull) == 0x8, "Class is the wrong size!");
