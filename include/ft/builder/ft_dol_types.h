#pragma once

// Classes that only exist in sora_melee as far as the fighter RELs are concerned.
// The REL code only needs their size, a constructor call and (for members) the destructor
// call, so these are "opaque": the real layout is unknown/irrelevant. Names come from the
// RTTI / vtables found in sora_melee. Replace an opaque class by a real one in the
// BrawlHeaders-style headers once it is understood (keep size and ctor/dtor signatures).

#include <types.h>

struct clTarget;
class soTeamModuleImpl;
class soKineticModuleGenericImpl;
class soModuleAccesser;
class soEventObserverRegistrationDesc;

// ---- opaque array elements -------------------------------------------------
#define FT_OPAQUE_STRUCT(Name, Size)                                                           \
    struct Name {                                                                              \
        u8 m_opaque[Size];                                                                     \
    }

FT_OPAQUE_STRUCT(soPartialAnim, 0x48);
FT_OPAQUE_STRUCT(soOtherAnim, 0x2C);
FT_OPAQUE_STRUCT(soTransitionTermPack, 0x14);
FT_OPAQUE_STRUCT(soMotionAnimObjCacheUnitChrRes, 0x8);


FT_OPAQUE_STRUCT(soShakeTerm, 0x1C);
#ifndef SO_CONTROLLER_CLATTER_DEFINED
#define SO_CONTROLLER_CLATTER_DEFINED
FT_OPAQUE_STRUCT(soControllerClatter, 0x14);
#endif
FT_OPAQUE_STRUCT(soEffectContinual, 0x2C);
FT_OPAQUE_STRUCT(soEffectTime, 0xC);
FT_OPAQUE_STRUCT(soPhysicsIKHandle, 0x38);

// ---- opaque element / helper classes with constructors in sora_melee -------
#include <so/collision/so_collision.h>

class soCollisionShieldPart {
    u8 m_opaque[0x60];
public:
    soCollisionShieldPart(soCollision::Category category, int kind);
    ~soCollisionShieldPart();
};

class soCollisionCatchPart {
    u8 m_opaque[0x5C];
public:
    soCollisionCatchPart(soCollision::Category category);
    ~soCollisionCatchPart();
};

// ---- opaque polymorphic modules (class lives in sora_melee) -------------------
#define FT_DOL_POLY_BEGIN(Name, Size) \
    class Name {                      \
        u8 m_opaque[(Size) - 4];      \
    public:                           \
        virtual ~Name()
#define FT_DOL_POLY_END }

template <typename T>
struct soMotionAnimObjCacheUnit {
    u8 m_opaque[8];
};

class soModuleAccesser;
class soEventObserverRegistrationDesc;
#include <so/so_array.h>
#include <so/damage/so_damage.h>
#include <so/controller/so_controller_impl.h>
#include <ef/ef_screen_handle.h>
#include <so/link/so_link_connection_server.h>

FT_DOL_POLY_BEGIN(soCatchModuleImpl, 0x64);
    soCatchModuleImpl(soModuleAccesser* acc, int n);
FT_DOL_POLY_END;

FT_DOL_POLY_BEGIN(soCaptureModuleImpl, 0x34);
    soCaptureModuleImpl(soModuleAccesser* acc);
FT_DOL_POLY_END;

FT_DOL_POLY_BEGIN(ftStopModuleImpl, 0x24);
    ftStopModuleImpl(soModuleAccesser* acc);
FT_DOL_POLY_END;

FT_DOL_POLY_BEGIN(soTurnModuleImpl, 0x38);
    soTurnModuleImpl(soModuleAccesser* acc);
FT_DOL_POLY_END;

FT_DOL_POLY_BEGIN(soShakeModuleImpl, 0x1C);
    soShakeModuleImpl(soModuleAccesser* acc, soArray<soShakeTerm>* terms, void* shakeData);
FT_DOL_POLY_END;

FT_DOL_POLY_BEGIN(soDamageModuleActor, 0x104);
    soDamageModuleActor(soModuleAccesser* acc, soArray<soDamage>* damages, void* null1, void* null2, soEventObserverRegistrationDesc* regDesc);
FT_DOL_POLY_END;

FT_DOL_POLY_BEGIN(soCollisionCatchModuleImpl, 0xE8);
    soCollisionCatchModuleImpl(soModuleAccesser* acc, int taskId, u8 category, soArray<soCollisionCatchPart>* parts, soEventObserverRegistrationDesc* regDesc, bool n1, bool n2);
FT_DOL_POLY_END;

FT_DOL_POLY_BEGIN(ftControllerModuleImpl, 0x16C);
    ftControllerModuleImpl(soModuleAccesser* acc, s16 unitId, soArray<soControllerImpl>* controllers, soArray<soControllerClatter>* clatters);
FT_DOL_POLY_END;

FT_DOL_POLY_BEGIN(soPhysicsModuleImpl, 0x48);
    soPhysicsModuleImpl(soModuleAccesser* acc, void* ikData, soArray<soPhysicsIKHandle>* handles, int n);
FT_DOL_POLY_END;

FT_DOL_POLY_BEGIN(soCollisionShieldEventPresenterShield, 0x10);
    soCollisionShieldEventPresenterShield(soModuleAccesser* acc);
FT_DOL_POLY_END;

FT_DOL_POLY_BEGIN(soCollisionShieldEventPresenterReflector, 0x10);
    soCollisionShieldEventPresenterReflector(soModuleAccesser* acc);
FT_DOL_POLY_END;

// ---- modules of the misc builders (ft_builder_misc.h) ------------------------------------------
FT_DOL_POLY_BEGIN(ftComboModuleImpl, 0x30);
    ftComboModuleImpl(soModuleAccesser* acc);
FT_DOL_POLY_END;

FT_DOL_POLY_BEGIN(soJostleModuleImpl, 0x4C);
    soJostleModuleImpl(soModuleAccesser* acc, int a, int b, void* jostleData);
FT_DOL_POLY_END;

FT_DOL_POLY_BEGIN(ftAbnormalModuleImpl, 0x68);
    ftAbnormalModuleImpl(soModuleAccesser* acc);
FT_DOL_POLY_END;

FT_DOL_POLY_BEGIN(ftGlowModuleImpl, 0x180);
    ftGlowModuleImpl(soModuleAccesser* acc);
FT_DOL_POLY_END;
