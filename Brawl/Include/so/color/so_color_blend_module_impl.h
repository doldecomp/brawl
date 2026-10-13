#pragma once

#include <StaticAssert.h>
#include <so/so_null.h>
#include <so/anim/so_anim_chr.h>
#include <so/event/so_event_presenter.h>
#include <so/status/so_status_event_presenter.h>
#include <so/model/so_model_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/color/so_color_blend.h>
#include <GX/GXTypes.h>

class soColorBlendModule: public soNullable {
public:
    // TODO: Fill out params for most of these.
    virtual bool isNull() const = 0;                                     // 0x8
    virtual ~soColorBlendModule();                                       // 0xc
    virtual void activate() = 0;                                         // 0x10
    virtual void deactivate() = 0;                                       // 0x14
    virtual void update() = 0;                                           // 0x18
    virtual void updateMaterial() = 0;                                   // 0x1C
    virtual void offAll(bool) = 0;                                       // 0x20
    virtual void setFlash(GXColor color, bool) = 0;                      // 0x24
    virtual void setFlashColorFrame(GXColor color, u32) = 0;             // 0x28
    virtual void offFlash(bool) = 0;                                     // 0x2C
    virtual void setLight(float, float, GXColor color, u8, bool) = 0;    // 0x30
    virtual void setLightColor(GXColor color, bool) = 0;                 // 0x34
    virtual void setLightColorFrame(GXColor color, bool) = 0;            // 0x38
    virtual void setLightDir(float, float, bool) = 0;                    // 0x3C
    virtual void offLight(bool) = 0;                                     // 0x40
    virtual void setPri(u32, bool) = 0;                                  // 0x44
    virtual void setSubColor(GXColor color, char enabled) = 0;           // 0x48
    virtual char isEnableSubColor() = 0;                                 // 0x4C
    virtual GXColor getSubColor() = 0;                                   // 0x50
    virtual soColorBlend *getColorBlend() = 0;                                    // 0x54
    virtual s8 getLightSet() = 0;                                      // 0x58
};

class soColorBlendModuleImpl: 
    public soColorBlendModule, 
    public soStatusEventObserver,
    public soAnimCmdEventObserver,
    public soModelEventObserver
{
public:
    // 0x2C
    soModuleAccesser* m_moduleAccesser;
    soColorBlend m_colorBlend1;
    soColorBlend m_colorBlend2;
    char _0x140[10];
    GXColor m_subColor;
    char _0x14e[1];
    bool m_useSubColor;
    char _0x150[4];

    virtual bool isNull() const;
    virtual ~soColorBlendModuleImpl();
    virtual void activate();
    virtual void deactivate();
    virtual void update();
    virtual void updateMaterial();
    virtual void offAll(bool);
    virtual void setFlash(GXColor color, bool);
    virtual void setFlashColorFrame(GXColor color, u32);
    virtual void offFlash(bool);
    virtual void setLight(float, float, GXColor color, u8, bool);
    virtual void setLightColor(GXColor color, bool);
    virtual void setLightColorFrame(GXColor color, bool);
    virtual void setLightDir(float, float, bool);
    virtual void offLight(bool);
    virtual void setPri(u32, bool);
    virtual void setSubColor(GXColor color, char enabled);
    virtual char isEnableSubColor();
    virtual GXColor getSubColor();
    virtual soColorBlend *getColorBlend();
    virtual s8 getLightSet();

    virtual bool isObserv(char unk1);
    virtual bool notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, int unk3);
    virtual void notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser);
    virtual void notifyEventConstructInstance(bool, soModuleAccesser* moduleAccesser);
};
static_assert(0x154 == sizeof(soColorBlendModuleImpl), "Class is wrong size!");

class soColorBlendModuleNull: public soColorBlendModule {
    virtual ~soColorBlendModuleNull();
    virtual void activate();
    virtual void deactivate();
    virtual void update();
    virtual void updateMaterial();
    virtual void offAll(bool);
    virtual void setFlash();
    virtual void setFlashColorFrame();
    virtual void offFlash(bool);
    virtual void setLight();
    virtual void setLightColor();
    virtual void setLightColorFrame();
    virtual void setLightDir();
    virtual void offLight(bool);
    virtual void setPri();
    virtual void setSubColor(GXColor color, char enabled);
    virtual char isEnableSubColor();
    virtual GXColor getSubColor();
    virtual soColorBlend *getColorBlend();
    virtual s8 getLightSet();

    soColorBlendModuleNull* getNullInstance();
};
