// MATCH-ONLY: retain the original fighter status scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/wario/ft_wario_status_uniq_process_special_s.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>

void ftWarioStatusUniqProcessSpecialSWheelie::initStatus(soModuleAccesser* a) {
    ftWarioStatusUniqProcessSpecialSCommon::initStatus(a);
}
void ftWarioStatusUniqProcessSpecialSWheelie::execStatus(soModuleAccesser* a) {
    soMotionModule& motion = a->getMotionModule();
    soLinkModule& link = a->getLinkModule();
    if (link.isLink(6)) {
        Vec3f rot = link.getParentRot(6);
        float frame = 45.0f - rot.m_x;
        if (frame < 0.0f) frame = 0.0f;
        else if (frame > 135.0f) frame = 135.0f;
        motion.setFrame(frame);
    }
}
void ftWarioStatusUniqProcessSpecialSWheelie::execFixPos(soModuleAccesser* a) {
    ftWarioStatusUniqProcessSpecialSCommon::execFixPos(a);
}
void ftWarioStatusUniqProcessSpecialSWheelie::exitStatus(soModuleAccesser* a, int next) {
    ftWarioStatusUniqProcessSpecialSCommon::exitStatus(a, next);
}
bool ftWarioStatusUniqProcessSpecialSWheelie::checkDamage(soModuleAccesser* a, void* info) {
    return ftWarioStatusUniqProcessSpecialSCommon::checkDamage(a, info);
}
ftWarioStatusUniqProcessSpecialSWheelie g_ftWarioStatusUniqProcessSpecialSWheelie;
