#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <ft/lucas/ft_lucas_status_uniq_process.h>
#include <so/so_module_accesser.h>
#include <so/collision/so_collision_shield_module_impl.h>
#include <so/effect/so_effect_module_impl.h>
#include <so/sound/so_sound_module_impl.h>
#include <so/work/so_work_manage_module_impl.h>

void ftLucasStatusUniqProcessSpecialLwHold::initStatus(soModuleAccesser* moduleAccesser) {
    // HYPOTHESIS: these flags configure Lucas's absorber group for PSI Magnet.
    moduleAccesser->getCollisionAbsorberModule().setStatus(0, 1, 0);

    soWorkManageModule& work = moduleAccesser->getWorkManageModule();
    if (work.getInt(0x20000003) < 0) {
        Vec3f position(0.0f, 6.5f, 10.0f);
        Vec3f rotation(0.0f, 0.0f, 0.0f);
        u32 effect = moduleAccesser->getEffectModule().req(
            static_cast<EfID>(0x1B000F), 2, &position, &rotation, 0.9f, nullptr, nullptr, false, 0xFFFFFFFF);
        work.setInt(effect, 0x20000003);
    }

    if (work.getInt(0x20000002) < 0) {
        int sound = moduleAccesser->getSoundModule().playSE(static_cast<SndID>(0x1450), true, 0, 0);
        work.setInt(sound, 0x20000002);
    }
}

void ftLucasStatusUniqProcessSpecialLwHold::exitStatus(
    soModuleAccesser* moduleAccesser, int nextStatus) {
    // 0x11F and 0x120 continue the native hold effect and sound lifetime.
    if (nextStatus != 0x11F && nextStatus != 0x120) {
        soWorkManageModule& work = moduleAccesser->getWorkManageModule();
        int effect = work.getInt(0x20000003);
        if (effect >= 0) {
            moduleAccesser->getEffectModule().kill(effect, true, true);
        }
        work.setInt(-1, 0x20000003);

        int sound = work.getInt(0x20000002);
        if (sound >= 0) {
            moduleAccesser->getSoundModule().stopSEHandle(sound, 0);
        }
        work.setInt(-1, 0x20000002);
    }
}

ftLucasStatusUniqProcessSpecialLwHold::~ftLucasStatusUniqProcessSpecialLwHold() {}

ftLucasStatusUniqProcessSpecialLwHold g_ftLucasStatusUniqProcessSpecialLwHold;
