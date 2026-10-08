// MATCH-ONLY: retain the original fighter status scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
// MATCH-ONLY: declaration order preserves the original module-local RTTI order.
#include <ft/ft_kinetic_energy.h>
#include <ft/wario/ft_wario_status_uniq_process_special_hi.h>
#include <so/so_module_accesser.h>
#include <math.h>

void ftWarioStatusUniqProcessSpecialHiJump::initStatus(soModuleAccesser* a) {
    soControllerModule& controller = a->getControllerModule();
    soKineticModule& kinetic = a->getKineticModule();
    soPostureModule& posture = a->getPostureModule();
    StageObject& fighter = a->getStageObject();
    ftWarioSpecialHiParam* param;
    if (fighter.soGetSubKind() == 0x15) {
        ftWario& wario = dynamic_cast<ftWario&>(fighter);
        param = wario.getExtendParam()->specialHi;
    } else {
        ftWarioMan& wario = dynamic_cast<ftWarioMan&>(fighter);
        param = wario.getExtendParam()->specialHi;
    }
    kinetic.changeKinetic(0x12, a);
    float stick = controller.getStickX();
    float lr = posture.getLr();
    float lrSign = (float)(lr < 0.0f ? -1 : 1);
    float stickSign = (float)(stick < 0.0f ? -1 : 1);
    float angle;
    if (stickSign == lrSign) angle = param->unk10 * stick;
    else angle = 0.0f;
    float radians = 0.017453292f * angle;
    ftKineticEnergyMotion& motion = dynamic_cast<ftKineticEnergyMotion&>(*kinetic.getEnergy(0));
    // HYPOTHESIS: this verified motion-energy field controls rotation of ascent.
    motion.unk3C = -radians;
}
void ftWarioStatusUniqProcessSpecialHiJump::exitStatus(soModuleAccesser* a, int next) {
    if (next == Fighter::Status::Fall_Special) {
        soKineticModule& kinetic = a->getKineticModule();
        soPostureModule& posture = a->getPostureModule();
        StageObject& fighter = a->getStageObject();
        ftWarioSpecialHiParam* param;
        if (fighter.soGetSubKind() == 0x15) {
            ftWario& wario = dynamic_cast<ftWario&>(fighter);
            param = wario.getExtendParam()->specialHi;
        } else {
            ftWarioMan& wario = dynamic_cast<ftWarioMan&>(fighter);
            param = wario.getExtendParam()->specialHi;
        }
        float speedY = param->unk18;
        float lr = posture.getLr();
        Vec2f speed(param->unk14 * lr, speedY);
        kinetic.changeKinetic(0x32, a);
        ftKineticEnergyStop& horizontal = dynamic_cast<ftKineticEnergyStop&>(*kinetic.getEnergy(3));
        Vec3f zero(0.0f, 0.0f, 0.0f);
        horizontal.resetEnergy(0x16, &speed, &zero, a);
        horizontal.enable();
    }
}
ftWarioStatusUniqProcessSpecialHiJump g_ftWarioStatusUniqProcessSpecialHiJump;
