#include <ft/ft_owner.h>
#include <ft/fighter.h>
#include <ft/ft_resource_id_accesser_impl.h>
#include <ft/kirby/ft_kirby_copy_ability_id_converter.h>
#include <ft/robot/ft_robot_transactor.h>
#include <wn/robot/wn_robot_beam.h>
#include <so/so_module_accesser.h>
#include <so/so_slow.h>

// Work variables (HYPOTHESIS names):
//   float 0x11000013  Robo Beam charge; recovers by 1 each frame until it passes const 0xfa6
//   int   0x10000040  kind of the lamp effect currently shown
//   int   0x10000041  handle of the lamp effect
//   int   0x10000044  generation counter of the beam articles
//   float 0x21000004  head tilt of the Robo Beam aim (see ftRobotStatusUniqProcessSpecialBeam)
//   flag  0x12000047  the beam charge does not recover (set while the beam is being shot)

// HYPOTHESIS: soTeam is opaque in the SDK; only its virtual at vtable +0x10 (the team number) is used here.
class soTeam {
public:
    virtual ~soTeam();
    virtual void reserved0C();
    virtual int getTeam();
};

ftRobotTransactor::ftRobotTransactor() { }
ftRobotTransactor::~ftRobotTransactor() { }

void ftRobotTransactor::init(soModuleAccesser* moduleAccesser) {
    moduleAccesser->getWorkManageModule().setFloat(moduleAccesser->getConstantFloatKirby(0xfa4), 0x11000013);
    int lampKind = getLampEffectKind(moduleAccesser->getWorkManageModule().getFloat(0x11000013), moduleAccesser);
    moduleAccesser->getEffectModule().killAll(0x10, true, true);
    Fighter& fighter = dynamic_cast<Fighter&>(moduleAccesser->getStageObject());
    if (fighter.getOwner()->getSpycloak() == 1) {
        moduleAccesser->getWorkManageModule().setInt(-1, 0x10000040);
        moduleAccesser->getWorkManageModule().setInt(-1, 0x10000041);
    } else {
        float z = moduleAccesser->getConstantFloatKirby(0xfad);
        float y = moduleAccesser->getConstantFloatKirby(0xfac);
        float x = moduleAccesser->getConstantFloatKirby(0xfab);
        Vec3f offset(x, y, z);
        Vec3f rot(0.0f, 0.0f, 0.0f);
        int handle = moduleAccesser->getEffectModule().reqFollow(static_cast<EfID>(lampKind), moduleAccesser->getConstantIntKirby(0x5dc1), &offset, &rot, 1.0f, false, 0x14, 0, -1);
        moduleAccesser->getWorkManageModule().setInt(lampKind, 0x10000040);
        moduleAccesser->getWorkManageModule().setInt(handle, 0x10000041);
    }
}

void ftRobotTransactor::initTransact(soModuleAccesser* moduleAccesser) {
    moduleAccesser->getWorkManageModule().setFloat(moduleAccesser->getConstantFloatKirby(0xfa4), 0x11000013);
    int lampKind = getLampEffectKind(moduleAccesser->getWorkManageModule().getFloat(0x11000013), moduleAccesser);
    moduleAccesser->getEffectModule().killAll(0x10, true, true);
    Fighter& fighter = dynamic_cast<Fighter&>(moduleAccesser->getStageObject());
    if (fighter.getOwner()->getSpycloak() == 1) {
        moduleAccesser->getWorkManageModule().setInt(-1, 0x10000040);
        moduleAccesser->getWorkManageModule().setInt(-1, 0x10000041);
    } else {
        float z = moduleAccesser->getConstantFloatKirby(0xfad);
        float y = moduleAccesser->getConstantFloatKirby(0xfac);
        float x = moduleAccesser->getConstantFloatKirby(0xfab);
        Vec3f rot(0.0f, 0.0f, 0.0f);
        Vec3f offset(x, y, z);
        int handle = moduleAccesser->getEffectModule().reqFollow(static_cast<EfID>(lampKind), moduleAccesser->getConstantIntKirby(0x5dc1), &offset, &rot, 1.0f, false, 0x14, 0, -1);
        moduleAccesser->getWorkManageModule().setInt(lampKind, 0x10000040);
        moduleAccesser->getWorkManageModule().setInt(handle, 0x10000041);
    }
}

void ftRobotTransactor::exit(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getWorkManageModule().getInt(0x10000041) >= 0) {
        int handle = moduleAccesser->getWorkManageModule().getInt(0x10000041);
        moduleAccesser->getEffectModule().kill(handle, true, true);
        moduleAccesser->getWorkManageModule().setInt(-1, 0x10000041);
    }
}

// The charge only recovers while the game is not paused for a hit stop.
void ftRobotTransactor::processUpdate(soModuleAccesser* moduleAccesser) {
    if (soSlow::getInstance()->isEstimate() == 1
        && moduleAccesser->getStopModule().isStop() == 0
        && moduleAccesser->getSlowModule().isSkip() == 0) {
        processUpdateSpecialNTransact(moduleAccesser);
    }
}

void ftRobotTransactor::processFixPosition(soModuleAccesser* moduleAccesser) {
    if (soSlow::getInstance()->isAdjust() == 1
        && moduleAccesser->getStopModule().isStop() == 0
        && moduleAccesser->getSlowModule().isSkip() == 0) {
        float charge = moduleAccesser->getWorkManageModule().getFloat(0x11000013);
        int shownKind = moduleAccesser->getWorkManageModule().getInt(0x10000040);
        int lampKind = getLampEffectKind(charge, moduleAccesser);
        Fighter& fighter = dynamic_cast<Fighter&>(moduleAccesser->getStageObject());
        if (fighter.getOwner()->getSpycloak() != 1 && shownKind != lampKind) {
            if (moduleAccesser->getWorkManageModule().getInt(0x10000041) >= 0) {
                int handle = moduleAccesser->getWorkManageModule().getInt(0x10000041);
                moduleAccesser->getEffectModule().kill(handle, true, true);
                moduleAccesser->getWorkManageModule().setInt(-1, 0x10000041);
            }
            float z = moduleAccesser->getConstantFloatKirby(0xfad);
            float y = moduleAccesser->getConstantFloatKirby(0xfac);
            float x = moduleAccesser->getConstantFloatKirby(0xfab);
            Vec3f offset(x, y, z);
            Vec3f rot(0.0f, 0.0f, 0.0f);
            int lampHandle = moduleAccesser->getEffectModule().reqFollow(static_cast<EfID>(lampKind), moduleAccesser->getConstantIntKirby(0x5dc1), &offset, &rot, 1.0f, false, 0x14, 0, -1);
            moduleAccesser->getWorkManageModule().setInt(lampKind, 0x10000040);
            moduleAccesser->getWorkManageModule().setInt(lampHandle, 0x10000041);
        }
    }
}

void ftRobotTransactor::processUpdateSpecialNTransact(soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getWorkManageModule().isFlag(0x12000047) != 1) {
        soWorkManageModule& work = moduleAccesser->getWorkManageModule();
        float threshold = moduleAccesser->getConstantFloatKirby(0xfa6);
        if (work.getFloat(0x11000013) < threshold) {
            moduleAccesser->getWorkManageModule().addFloat(1.0f, 0x11000013);
        }
    }
}

// Swaps the lamp effect when the charge crosses into another colour band.
void ftRobotTransactor::processUpdateEffectTransact(soModuleAccesser* moduleAccesser) {
    float charge = moduleAccesser->getWorkManageModule().getFloat(0x11000013);
    int shownKind = moduleAccesser->getWorkManageModule().getInt(0x10000040);
    int lampKind = getLampEffectKind(charge, moduleAccesser);
    Fighter& fighter = dynamic_cast<Fighter&>(moduleAccesser->getStageObject());
    if (fighter.getOwner()->getSpycloak() != 1 && shownKind != lampKind) {
        if (moduleAccesser->getWorkManageModule().getInt(0x10000041) >= 0) {
            int handle = moduleAccesser->getWorkManageModule().getInt(0x10000041);
            moduleAccesser->getEffectModule().kill(handle, true, true);
            moduleAccesser->getWorkManageModule().setInt(-1, 0x10000041);
        }
        float z = moduleAccesser->getConstantFloatKirby(0xfad);
        float y = moduleAccesser->getConstantFloatKirby(0xfac);
        float x = moduleAccesser->getConstantFloatKirby(0xfab);
        Vec3f rot(0.0f, 0.0f, 0.0f);
        Vec3f offset(x, y, z);
        int lampHandle = moduleAccesser->getEffectModule().reqFollow(static_cast<EfID>(lampKind), moduleAccesser->getConstantIntKirby(0x5dc1), &offset, &rot, 1.0f, false, 0x14, 0, -1);
        moduleAccesser->getWorkManageModule().setInt(lampKind, 0x10000040);
        moduleAccesser->getWorkManageModule().setInt(lampHandle, 0x10000041);
    }
}

// HYPOTHESIS: the resource id accessor's virtual at vtable +0x5c (listed as getKirbyResId() in the SDK headers) takes
// the kind of resource to look up; this view calls it with that argument.
static u32 ftRobotGetKirbyResId(ftResourceIdAccesserImpl& resources, int kind) {
    typedef u32 (*GetResId)(ftResourceIdAccesserImpl*, int);
    void** table = *reinterpret_cast<void***>(&resources);
    return reinterpret_cast<GetResId>(table[0x5c / sizeof(void*)])(&resources, kind);
}

bool ftRobotTransactor::activeArticle(soArticle* article, soModuleAccesser* moduleAccesser) {
    bool result;
    if (article->getArticleId() == 0xd) {
        wnRobotBeam* beam = dynamic_cast<wnRobotBeam*>(article);
        if (beam == NULL) {
            result = false;
        } else {
            ftResourceIdAccesserImpl& resources = dynamic_cast<ftResourceIdAccesserImpl&>(*moduleAccesser->getResourceModule().getResourceIdAccesser());
            u32 resourceId = ftRobotGetKirbyResId(resources, 0x23);
            result = activeArticle1(beam, moduleAccesser, resourceId);
        }
    } else {
        result = false;
    }
    return result;
}

bool ftRobotTransactor::activeArticle1(wnRobotBeam* weapon, soModuleAccesser* acc, u32 resourceId) {
    g_ftKirbyCopyAbilityIdConverter.convCorrectToOrigId(0, acc->getStatusModule().getStatusKind(), acc, true);
    float lr = acc->getPostureModule().getLr();
    s32 boneId = acc->getConstantIntKirby(24000);
    Vec3f muzzle;
    if (acc->getSituationModule().getKind() == 2) {
        Vec3f local;
        local.m_x = 0.0f;
        local.m_y = acc->getConstantFloatKirby(0xfaa);
        local.m_z = acc->getConstantFloatKirby(0xfa9);
        muzzle = acc->getModelModule().getNodeGlobalPosition(boneId, &local, false, false);
    } else {
        Vec3f local;
        local.m_x = 0.0f;
        local.m_y = acc->getConstantFloatKirby(0xfa8);
        local.m_z = acc->getConstantFloatKirby(0xfa7);
        muzzle = acc->getModelModule().getNodeGlobalPosition(boneId, &local, false, false);
    }
    bool lowCharge = false;
    if (acc->getWorkManageModule().getFloat(0x11000013) >= acc->getConstantFloatKirby(0xfa6)) {
        lowCharge = true;
    }
    soWorkManageModule& work = acc->getWorkManageModule();
    soTeamModule& teamModule = acc->getTeamModule();
    s32 founderTaskId = acc->getStageObject().m_taskId;
    s32 variant = work.getInt(0x10000044);
    float angle = work.getFloat(0x21000004);
    s32 team = teamModule.getTeam()->getTeam();
    weapon->activate(lr, angle, founderTaskId, resourceId, team, &muzzle, lowCharge, variant);
    return false;
}

// HYPOTHESIS: colour bands of the lamp: up to const 0xfa5 red, up to 0xfa6 yellow, otherwise green. Kirby uses the
// effect set of his copy ability.
int ftRobotTransactor::getLampEffectKind(float charge, soModuleAccesser* moduleAccesser) {
    int subKind = moduleAccesser->getStageObject().soGetSubKind();
    int kind;
    if (charge <= moduleAccesser->getConstantFloatKirby(0xfa5)) {
        kind = subKind == 5 ? 0x1250002 : 0x24000c;
    } else if (charge >= moduleAccesser->getConstantFloatKirby(0xfa6)) {
        kind = subKind == 5 ? 0x1250004 : 0x24000e;
    } else {
        kind = subKind == 5 ? 0x1250003 : 0x24000d;
    }
    return kind;
}
