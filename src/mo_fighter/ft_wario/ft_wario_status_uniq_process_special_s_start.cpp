// MATCH-ONLY: retain the original fighter status scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/wario/ft_wario_status_uniq_process_special_s.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>

void ftWarioStatusUniqProcessSpecialSStart::execFixPos(soModuleAccesser*) {}
void ftWarioStatusUniqProcessSpecialSStart::exitStatus(soModuleAccesser* a, int next) {
    ftWarioStatusUniqProcessSpecialSCommon::exitStatus(a, next);
    if (next == 0x124) {
        soLinkModule& link = a->getLinkModule();
        if (link.isLink(6)) {
            Vec2f speed;
            Vec2f::copy(speed, a->getKineticModule().getSumSpeed(soKineticEnergy::AttributeFlag(1)));
            ftWarioBikeSpeedEvent event(0x455);
            event.speed.m_x = speed.m_x;
            event.speed.m_y = speed.m_y;
            int node = a->getModelModule().getCorrectNodeId(0x130);
            link.sendEventParents(6, event);
            link.setModelConstraintPosOrt(6, node, 8, 3, false);
            a->getSituationModule().setKind(Situation_Air, false);
        }
    }
}
ftWarioStatusUniqProcessSpecialSStart g_ftWarioStatusUniqProcessSpecialSStart;
