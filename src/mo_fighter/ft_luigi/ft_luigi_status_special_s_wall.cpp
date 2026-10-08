#include <ft/luigi/ft_luigi_status_special_s.h>
#include <ft/ft_kinetic_energy.h>
#include <ft/ft_util.h>
#include <so/so_module_accesser.h>
#include <so/motion/so_motion_module_impl.h>
#include <so/motion/so_motion_change_param.h>
#include <so/ground/so_ground_module_impl.h>
#include <so/kinetic/so_kinetic_module_impl.h>

void ftLuigiStatusUniqProcessSpecialSWall::initStatus(soModuleAccesser* moduleAccesser) {
    moduleAccesser->getGroundModule().update(1);
    soMotionChangeParam motion(0x1D5, 0.0f, 1.0f, 0, 0, 0, 0);
    moduleAccesser->getMotionModule().changeMotionRequest(&motion);

    float lr = moduleAccesser->getPostureModule().getLr();
    bool facingLeft = (lr == -1.0f);
    moduleAccesser->getGroundModule().attach(facingLeft ? 2 : 4, 0);

    ftUtil::adjustWall(moduleAccesser, lr, -lr, -1.0f, 1);
    ftUtil::adjustWall(moduleAccesser, lr, facingLeft ? 1.0f : 0.0f, 1.0f, 0);

    soKineticEnergyGroundMovement& groundMovement =
        dynamic_cast<soKineticEnergyGroundMovement&>(
            *moduleAccesser->getKineticModule().getEnergy(6));
    Vec2f attachNormal = moduleAccesser->getGroundModule().getAttachNormal(0);
    groundMovement.enableRot(&attachNormal);

    moduleAccesser->getKineticModule().getEnergy(5)->disable();
}

ftLuigiStatusUniqProcessSpecialSWall g_ftLuigiStatusUniqProcessSpecialSWall;
