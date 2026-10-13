#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <types.h>

class soModuleAccesser;

class soSlowModule : public soNull, public soNullable {
public:
    virtual ~soSlowModule();
    virtual void activate();
    virtual void deactivate();
    virtual void update(bool);
    virtual void resetSkip();
    virtual bool isSlow();
    virtual void set(int mag, int frame);
    virtual int getMag();
    virtual int getFrame();
    virtual void clear();
    virtual float getRate();
    virtual bool isSkip();
    virtual void setWhole(int, int wholeFrame);
    virtual void clearWhole();
    virtual u8 getWholeMag();
    virtual void setWholeFrame(int wholeFrame);
    virtual int getWholeFrame();
};
static_assert(sizeof(soSlowModule) == 12, "Class is wrong size!");

class soSlowModuleSimple : public soSlowModule {
    soModuleAccesser* m_moduleAccesser;
    float m_rate;
    bool m_isSkip;
    char _pad[3];

public:
    virtual ~soSlowModuleSimple();
    virtual void activate();
    virtual void deactivate();
    virtual void update(bool);
    virtual void resetSkip();
    virtual bool isSlow();
    virtual void set(int mag, int frame);
    virtual int getMag();
    virtual int getFrame();
    virtual void clear();
    virtual float getRate();
    virtual bool isSkip();
    virtual void setWhole(int, int wholeFrame);
    virtual void clearWhole();
    virtual u8 getWholeMag();
    virtual void setWholeFrame(int wholeFrame);
    virtual int getWholeFrame();
};
static_assert(sizeof(soSlowModuleSimple) == 24, "Class is wrong size!");
