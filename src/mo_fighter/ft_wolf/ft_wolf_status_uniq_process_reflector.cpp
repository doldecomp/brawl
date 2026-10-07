#include <ft/wolf/ft_wolf.h>
#include <ft/wolf/ft_wolf_status_uniq_process_reflector.h>
#include <so/so_module_accesser.h>

void ftWolfStatusUniqProcessReflectorImpl::setTurn(soModuleAccesser* moduleAccesser) {
    ftWolfData* data = dynamic_cast<ftWolf&>(moduleAccesser->getStageObject()).m_commonData;
    const soModuleEnumeration& modules = *moduleAccesser->m_enumerationStart;
    soTurnModule& turn = *static_cast<soTurnModule*>(modules.m_turnModule);
    // The shared process requests this when the stick opposes Wolf's facing.
    // Start his reflector rotation using the current facing and character turn data.
    turn.set(&data->reflectorTurnData, true, false, modules.m_postureModule->getLr());
}
