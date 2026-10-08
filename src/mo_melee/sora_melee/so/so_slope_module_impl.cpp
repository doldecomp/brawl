#include <so/ground/so_ground_module_impl.h>
#include <so/model/so_model_module_impl.h>
#include <so/posture/so_posture_module_impl.h>
#include <so/situation/so_situation_module_impl.h>
#include <so/slope/so_slope_module_impl.h>
#include <so/so_module_accesser.h>

// Slope module: tilts the fighter's top (and left/right/part) joints to the angle of the ground it stands on.

// Resets the module: no slope status, no queued change, flat ground.
void soSlopeModuleImpl::activate() {
    setStatus(0, 0, false);
    changeStatus();
    m_slopeAngle = 0.0f;
    m_topAngle[0] = m_topAngle[1] = 0;
    m_leftAngle[0] = m_leftAngle[1] = 0;
    m_rightAngle[0] = m_rightAngle[1] = 0;
    m_partAngle = 0;
    m_0x6C = 0xFFFF;
    setTopAngleUnlimit(false);
    m_statusParamArrayVector.clear();
}

// Queues a status change; it is applied by changeStatus(). Statuses the module was told to ignore are dropped.
void soSlopeModuleImpl::setStatus(u32 statusMask, int angle, bool isPart) {
    soSlopeStatusParam param;
    param.m_status.m_mask = statusMask & ~m_invalidStatus.m_mask;
    param.m_0x4 = angle;
    param.m_0x8 = isPart;
    if (m_statusParamArrayVector.isEmpty() == false)
        m_statusParamArrayVector.clear();
    m_statusParamArrayVector.push(param);
}

// Applies the queued status: parts that become active start at the queued angle.
void soSlopeModuleImpl::changeStatus() {
    if (m_statusParamArrayVector.isEmpty() == false) {
        const soSlopeStatusParam& param = m_statusParamArrayVector.at(0);
        u32 prevStatus = m_status.m_mask;
        m_status.m_mask = param.m_status.m_mask;
        if (param.m_0x8 == true) {
            m_partAngle = param.m_0x4;
        } else {
            if ((m_status.m_mask & soSlopeStatusParam::STATUS_MASK_TOP) != (prevStatus & soSlopeStatusParam::STATUS_MASK_TOP))
                m_topAngle[0] = m_topAngle[1] = param.m_0x4;
            if ((m_status.m_mask & soSlopeStatusParam::STATUS_MASK_L) != (prevStatus & soSlopeStatusParam::STATUS_MASK_L))
                m_leftAngle[0] = m_leftAngle[1] = param.m_0x4;
            if ((m_status.m_mask & soSlopeStatusParam::STATUS_MASK_R) != (prevStatus & soSlopeStatusParam::STATUS_MASK_R))
                m_rightAngle[0] = m_rightAngle[1] = param.m_0x4;
            m_partAngle = 0;
        }
        m_statusParamArrayVector.clear();
    }
}

// Tilts the model's top (or part) node to the slope while the fighter stands on the ground.
void soSlopeModuleImpl::updateModelTopAngle() {
    if (m_moduleAccesser->getSituationModule().getKind() != 0)
        return;
    if (m_moduleAccesser->getGroundModule().isTouch(8, 0) != true)
        return;
    if (m_slopeAngle == 0.0f)
        return;
    int node;
    if (m_status.m_mask & soSlopeStatusParam::STATUS_MASK_PART)
        node = m_partNode;
    else
        node = 0;
    Vec3f rotate = m_moduleAccesser->getModelModule().getNodeRotate(node);
    // HYPOTHESIS: byte 0x7c selects tilting around X (scaled by the model's facing) instead of around Z.
    if (m_0x7C == 0)
        rotate.m_x = m_slopeAngle * m_moduleAccesser->getPostureModule().getRotYLr() / 57.29578f;
    else
        rotate.m_z = -m_slopeAngle;
    m_moduleAccesser->getModelModule().setNodeRotate(node, &rotate);
}

void soSlopeModuleImpl::setTopAngleUnlimit(bool isUnlimit) {
    m_isTopAngleUnlimit = isUnlimit;
}

bool soSlopeModuleImpl::isObserv(char kind) {
    return kind == 0x18;
}

// HYPOTHESIS: the status data's fourth word starts with flags; the third-from-last bit marks statuses that follow the
// ground slope. The SDK declares soStatusData as an empty struct, so this view stands in for the real fields.
struct soSlopeStatusDataView {
    u32 m_0;
    u32 m_4;
    u32 m_8;
    u32 : 29;
    u32 m_followsSlope : 1;
    u32 : 2;
};

// A status that does not use the slope clears the slope and the unlimited-top-angle flag.
void soSlopeModuleImpl::notifyEventChangeStatus(int statusKind, int prevStatusKind, soStatusData* statusData, soModuleAccesser* moduleAccesser) {
    if (reinterpret_cast<soSlopeStatusDataView*>(statusData)->m_followsSlope == 0) {
        setStatus(0, 0, false);
        m_partAngle = 0;
        setTopAngleUnlimit(false);
    }
}

void soSlopeModuleImpl::setInvalidStatus(u32 statusMask) {
    m_invalidStatus.m_mask = statusMask;
}

void soSlopeModuleImpl::setPartNode(int partNode) {
    m_partNode = partNode;
}

soSlopeStatusParam::Status soSlopeModuleImpl::getStatus() {
    return m_status;
}
