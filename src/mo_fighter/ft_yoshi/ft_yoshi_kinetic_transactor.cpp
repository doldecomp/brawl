#include <ft/builder/ft_dol_array_list.h>
// MATCH-ONLY: retain the local Vec2f ctor/assignment calls used by the native helpers.
#define MT_VEC2F_CTOR_NOINLINE
#define MT_VEC2F_ASSIGN_NOINLINE
#include <ft/yoshi/ft_yoshi_kinetic_transactor.h>
#include <ft/yoshi/ft_yoshi_special_s_param.h>
#include <ft/yoshi/ft_yoshi_final_param.h>
#include <ft/ft_common_data_accesser.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_kinetic_utility.h>
#include <so/so_module_accesser.h>
#include <ft/builder/ft_builder_kinetic.h>


void ftYoshiKineticTransactor::changeKinetic(int mode, void* pools, soModuleAccesser* acc) {
    if (mode <= 0x63) {
        ftKineticTransactor::changeKinetic(mode, pools, acc);
        return;
    }

    // Native code preprocesses every custom mode before rejecting values > 0x68.
    Vec2f speed = ftKineticTransactHelper::preHelpProcess(acc, 1, 1);
    bool unkFlag = false;
    switch (mode) {
    case 0x64:
        ftYoshiKineticTransactor::changeKineticSub(&unkFlag, pools, &speed, acc);
        break;
    case 0x65:
        ftYoshiKineticTransactor::changeKineticSub1(&unkFlag, pools, &speed, acc);
        break;
    case 0x66:
        ftYoshiKineticTransactor::changeKineticSub2(&unkFlag, pools, &speed, acc);
        break;
    case 0x67:
        ftYoshiKineticTransactor::changeKineticSub3(&unkFlag, pools, &speed, acc);
        break;
    case 0x68:
        ftYoshiKineticTransactor::changeKineticSub4(&unkFlag, pools, &speed, acc);
        break;
    default:
        return;
    }
    ftKineticTransactor::enableOutsideEnergy(acc);
}

// Native custom kinetic mode 0x64 (Egg Roll stop energy). The bool passed by
// the dispatcher is unused in this helper.
void ftYoshiKineticTransactor::changeKineticSub(bool*, void*, Vec2f*, soModuleAccesser* acc) {
    ftYoshiSpecialSParam* param = static_cast<ftYoshiSpecialSParam*>(
        g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[0]);
    float initialHorizontalSpeed = param->unk2C * acc->getPostureModule().getLr();
    Vec2f initialSpeed(initialHorizontalSpeed, 0.0f);
    Vec3f rotation(0.0f, 0.0f, 0.0f);
    soKineticUtility::resetEnableEnergy(3, acc, 0, &initialSpeed, &rotation);

    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(
        *acc->getKineticModule().getEnergy(3));
    stop.m_accel = Vec2f(initialHorizontalSpeed, 0.0f);
    stop.m_brake = Vec2f(param->unk30, 0.0f);
    stop.m_speedTarget = Vec2f(param->minimumGroundSpeed, 0.0f);
    stop.m_speedLimit = Vec2f(param->unk38, 0.0f);
}

// Native custom kinetic mode 0x65. The extension record fields are kept
// numeric where their use does not establish a semantic name.
void ftYoshiKineticTransactor::changeKineticSub1(bool*, void*, Vec2f* speed, soModuleAccesser* acc) {
    ftYoshiSpecialSParam* param = static_cast<ftYoshiSpecialSParam*>(
        g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[0]);
    Vec3f rotation(0.0f, 0.0f, 0.0f);
    Vec2f gravitySpeed(0.0f, speed->m_y);
    soKineticUtility::resetEnableEnergy(1, acc, 0, &gravitySpeed, &rotation);
    Vec2f controllerSpeed(speed->m_x, 0.0f);
    soKineticUtility::resetEnableEnergy(2, acc, 0, &controllerSpeed, &rotation);

    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(
        *acc->getKineticModule().getEnergy(1));
    ftKineticEnergyController& controller = dynamic_cast<ftKineticEnergyController&>(
        *acc->getKineticModule().getEnergy(2));
    controller.m_accelMul = param->unk98;
    controller.m_speedLimit = Vec2f(param->unk48, 0.0f);
    controller.m_speedTarget = Vec2f(param->minimumAirSpeed, 0.0f);
    gravity.m_gravity = -param->gravity;
    gravity.m_fallSpeedMax = param->gravityLimit;
    gravity.unk1C = param->gravityLimit;
}


// Native custom kinetic mode 0x66 selects Stop, Gravity, or Controller energy
// according to the pre-transition speed and the fourth Yoshi extension record.
void ftYoshiKineticTransactor::changeKineticSub2(bool*, void*, Vec2f* speed, soModuleAccesser* acc) {
    float lr = acc->getPostureModule().getLr();
    ftYoshiFinalParam* param = static_cast<ftYoshiFinalParam*>(
        g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[3]);
    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(
        *acc->getKineticModule().getEnergy(3));
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(
        *acc->getKineticModule().getEnergy(1));
    ftKineticEnergyController& controller = dynamic_cast<ftKineticEnergyController&>(
        *acc->getKineticModule().getEnergy(2));
    acc->getKineticModule().unableEnergyAll();

    float horizontalSpeed = speed->m_x;
    float verticalSpeed = speed->m_y;
    float horizontalLimit = param->unk00;
    bool useStop = horizontalSpeed * lr <= horizontalLimit && horizontalSpeed * lr >= 0.0f;
    Vec2f stopSpeed(useStop ? horizontalSpeed * lr : 0.0f, 0.0f);
    Vec2f controllerSpeed(useStop ? 0.0f : horizontalSpeed, 0.0f);

    float verticalLimit = param->unk20;
    bool useGravity = verticalSpeed >= -verticalLimit && verticalSpeed <= 0.0f;
    Vec2f gravitySpeed(0.0f, useGravity ? verticalSpeed : 0.0f);
    controllerSpeed.m_y = useGravity ? -verticalLimit : verticalSpeed;
    Vec3f rotation(0.0f, 0.0f, 0.0f);
    if (useStop) {
        stop.enable();
    }
    if (useGravity) {
        gravity.enable();
    }

    stop.resetEnergy(0x16, &stopSpeed, &rotation, acc);
    stop.m_accel = Vec2f(0.0f, 0.0f);
    stop.m_speedTarget = Vec2f(param->unk00, 0.0f);
    stop.m_speedLimit = Vec2f(param->unk00, 0.0f);
    stop.m_brake = Vec2f(0.0f, 0.0f);

    gravity.resetEnergy(0, &gravitySpeed, &rotation, acc);
    gravity.m_gravity = -param->unk1C;
    gravity.m_fallSpeedMax = param->unk20;
    gravity.unk18 = 0.0f;
    gravity.unk1C = param->unk20;

    Vec2f controllerInitialSpeed(0.0f, 0.0f);
    controller.resetEnergy(0x0B, &controllerInitialSpeed, &rotation, acc);
    controller.m_speed = controllerSpeed;
    controller.m_accelMul = param->unk04;
    controller.m_unk40 = 0.0f;
    controller.m_unk44 = param->unk10;
    controller.m_unk48 = 0.0f;
    controller.m_speedTarget = Vec2f(param->unk08, param->unk14);
    controller.m_speedLimit = Vec2f(param->unk08, param->unk14);
    controller.m_brake = Vec2f(param->unk0C, param->unk18);
    controller.enable();
}

// Native custom kinetic mode 0x67 is the related air configuration. The Stop
// cast is retained because the native function performs that checked cast.
void ftYoshiKineticTransactor::changeKineticSub3(bool*, void*, Vec2f* speed, soModuleAccesser* acc) {
    // MATCH-ONLY: native calls this getter and discards its returned LR value.
    acc->getPostureModule().getLr();
    ftYoshiFinalParam* param = static_cast<ftYoshiFinalParam*>(
        g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[3]);
    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(
        *acc->getKineticModule().getEnergy(3));
    (void)stop;
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(
        *acc->getKineticModule().getEnergy(1));
    ftKineticEnergyController& controller = dynamic_cast<ftKineticEnergyController&>(
        *acc->getKineticModule().getEnergy(2));
    acc->getKineticModule().unableEnergyAll();

    float verticalLimit = param->unk20;
    float verticalSpeed = speed->m_y;
    bool useGravity = verticalSpeed >= -verticalLimit && verticalSpeed <= 0.0f;
    Vec2f gravitySpeed(0.0f, useGravity ? verticalSpeed : 0.0f);
    Vec2f controllerSpeed(speed->m_x, useGravity ? -verticalLimit : verticalSpeed);
    Vec3f rotation(0.0f, 0.0f, 0.0f);
    if (useGravity) {
        gravity.enable();
    }

    gravity.resetEnergy(0, &gravitySpeed, &rotation, acc);
    gravity.m_gravity = -param->unk1C;
    gravity.m_fallSpeedMax = verticalLimit;
    gravity.unk18 = 0.0f;
    gravity.unk1C = verticalLimit;

    Vec2f controllerInitialSpeed(0.0f, 0.0f);
    controller.resetEnergy(0x0B, &controllerInitialSpeed, &rotation, acc);
    controller.m_speed = controllerSpeed;
    controller.m_accelMul = param->unk04;
    controller.m_unk40 = 0.0f;
    controller.m_unk44 = param->unk10;
    controller.m_unk48 = 0.0f;
    controller.m_speedTarget = Vec2f(param->unk08, param->unk14);
    controller.m_speedLimit = Vec2f(param->unk08, param->unk14);
    controller.m_brake = Vec2f(param->unk0C, param->unk18);
    controller.enable();
}

// Native custom kinetic mode 0x68 configures the Stop and Gravity energies.
// The extension-record field meanings remain unknown; retain numeric names.
void ftYoshiKineticTransactor::changeKineticSub4(bool*, void*, Vec2f* speed, soModuleAccesser* acc) {
    ftYoshiFinalParam* param = static_cast<ftYoshiFinalParam*>(
        g_ftCommonDataAccesser.getData(Fighter_Yoshi)->extendParam[3]);
    ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(
        *acc->getKineticModule().getEnergy(3));
    ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(
        *acc->getKineticModule().getEnergy(1));

    Vec2f initialSpeed(speed->m_x, 0.0f);
    Vec3f rotation(0.0f, 0.0f, 0.0f);
    stop.resetEnergy(0x16, &initialSpeed, &rotation, acc);

    float turnRate = param->unk04 * acc->getPostureModule().getLr();
    stop.m_accel = Vec2f(turnRate, 0.0f);
    stop.m_speedTarget = Vec2f(param->unk00, 0.0f);
    stop.m_speedLimit = Vec2f(param->unk08, 0.0f);
    stop.m_brake = Vec2f(param->unk0C, 0.0f);
    stop.enable();

    gravity.m_gravity = -param->unk18;
    gravity.m_fallSpeedMax = param->unk20;
    gravity.unk18 = param->unk18;
    gravity.unk1C = param->unk14;
    gravity.enable();
}
