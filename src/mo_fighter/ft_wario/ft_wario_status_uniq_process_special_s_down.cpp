// MATCH-ONLY: retain the original fighter status scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/wario/ft_wario_status_uniq_process_special_s.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>

void ftWarioStatusUniqProcessSpecialSDown::initStatus(soModuleAccesser* a) {
    soKineticModule& kinetic = a->getKineticModule();
    soLinkModule& link = a->getLinkModule();
    if (link.isLink(6)) {
        ftWarioBikeSpeedEvent event(0x458);
        link.sendEventParents(6, event);
        Vec2f speed;
        Vec2f::copy(speed, event.speed);
        ftKineticEnergyStop& horizontal = dynamic_cast<ftKineticEnergyStop&>(*kinetic.getEnergy(3));
        ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));
        horizontal.m_speed = Vec2f(speed.m_x, 0.0f);
        gravity.m_speedY = speed.m_y;
        link.removeModelConstraint(true);
        link.unlink(6);
    }
}
ftWarioStatusUniqProcessSpecialSDown g_ftWarioStatusUniqProcessSpecialSDown;
