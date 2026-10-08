#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <wn/wario/wn_wario_bike_status_uniq_process.h>
#include <wn/wario/wn_wario_bike_link_event.h>
#include <it/it_manager.h>
#include <it/item.h>
#include <so/so_module_accesser.h>


void wnWarioBikeStatusUniqProcessItem::initStatus(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soKineticModule& kinetic = a->getKineticModule();
    soPostureModule& posture = a->getPostureModule();
    soModelModule& model = a->getModelModule();
    soLinkModule& link = a->getLinkModule();
    if (link.isModelConstraint()) link.removeModelConstraint(true);
    Vec3f spawnPosition = model.getNodeGlobalPosition(9, false);
    bool grounded = a->getGroundModule().isTouch((grCollStatus::TouchMask)8, 0);
    if (!grounded) spawnPosition.m_y += 0.1f;
    float facing = posture.getLr();
    int brresId = work.getInt(0x10000006);
    u8 groupNo = (u8)work.getInt(0x10000005);
    soResourceModule* resource = &a->getResourceModule();
    int ownerTaskId = link.getParentTaskId(3);
    BaseItem* bike = itManager::getInstance()->createItem(
        &spawnPosition, &spawnPosition, facing, Item_Wario_Bike, 0,
        ownerTaskId, resource, groupNo, brresId, 0, -1);
    if (bike) {
        bike->setOwnerScale(posture.getScale());
        Vec3f rotation(0.0f, 0.0f, 0.0f);
        bike->resetRotation(&rotation);
        Vec2f velocity = kinetic.getSumSpeed(soKineticEnergy::AttributeFlag(-1));
        Vec3f speed(velocity.m_x, velocity.m_y, 0.0f);
        bike->addSpeed(&speed, true);
        bike->resetDamage();
        ftWarioBikeTaskEvent event(0x45C, bike->getTaskId());
        link.sendEventNodes(7, event, 0);
    }
    work.onFlag(0x2200000B);
}

wnWarioBikeStatusUniqProcessItem g_wnWarioBikeStatusUniqProcessItem;
