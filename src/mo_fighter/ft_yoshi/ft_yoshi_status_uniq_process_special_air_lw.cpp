#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/yoshi/ft_yoshi_status_uniq_process.h>
#include <ft/ft_common_data_accesser.h>
#include <ft/ft_kinetic_energy.h>
#include <so/so_module_accesser.h>

// Local partial layout: the original load verifies a parameter pointer at 0x84.
// HYPOTHESIS: this fighter-specific pointer selects down-special
// fall parameters. Its first float supplies the gravity energy's vertical speed.
struct ftYoshiSpecialLwParam {
    float speedY;
};
struct ftYoshiData {
    u8 unk0[0x84];
    ftYoshiSpecialLwParam* specialLwParam;
};

void ftYoshiStatusUniqProcessSpecialAirLw::execStatus(soModuleAccesser* moduleAccesser) {
    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    soKineticModule& kinetic = moduleAccesser->getKineticModule();
    // Allow cliff checks during the downward phase of the move.
    moduleAccesser->getGroundModule().setCliffCheck(soGroundShapeImpl::Cliff_Check_On_Drop, 0);
    ftYoshiSpecialLwParam* param =
        reinterpret_cast<ftYoshiData*>(g_ftCommonDataAccesser.getData(Fighter_Yoshi))->specialLwParam;
    // HYPOTHESIS: this animation flag begins the downward attack phase.
    if (work.isFlag(0x22000011)) {
        kinetic.changeKinetic(0, moduleAccesser);
        kinetic.unableEnergy(2);
        ftKineticEnergyGravity& gravity = dynamic_cast<ftKineticEnergyGravity&>(*kinetic.getEnergy(1));
        gravity.m_speedY = param->speedY;
        gravity.m_gravity = 0.0f;
    }
}

ftYoshiStatusUniqProcessSpecialAirLw g_ftYoshiStatusUniqProcessSpecialAirLw;
