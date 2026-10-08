// MATCH-ONLY: retain native fighter-module scheduling.
#pragma scheduling off
#define SO_STATUS_UNIQ_PROCESS_OUT_OF_LINE
#include <wn/wario/wn_wario_bike_status_uniq_process.h>
#include <so/so_module_accesser.h>
#include <st/st_utility.h>
#include <math.h>

void wnWarioBikeStatusUniqProcessUtility::execStatus(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soKineticModule& kinetic = a->getKineticModule();
    soModelModule& model = a->getModelModule();
    float speed = kinetic.getSumSpeed(soKineticEnergy::AttributeFlag(-1)).length();
    float phase17 = work.getFloat(0x21000004);
    float phase11 = work.getFloat(0x21000005);
    float step17;
    if (work.isFlag(0x22000004)) {
        float radius = 2.4f * a->getPostureModule().getScale();
        float circumference = 6.2831855f * radius;
        step17 = 360.0f * speed / circumference;
        work.setFloat(step17, 0x21000006);
    } else {
        step17 = work.getFloat(0x21000006) * 0.99f;
        work.setFloat(step17, 0x21000006);
    }
    float step11;
    if (work.isFlag(0x22000005)) {
        float radius = 5.5f * a->getPostureModule().getScale();
        float circumference = 6.2831855f * radius;
        step11 = 360.0f * speed / circumference;
        work.setFloat(step11, 0x21000007);
    } else {
        step11 = work.getFloat(0x21000007);
    }
    phase17 += step17;
    phase11 += step11;
    if (phase17 > 360.0f) phase17 -= 360.0f;
    if (phase11 > 360.0f) phase11 -= 360.0f;
    model.setNodeRotateX(0x11, phase11);
    model.setNodeRotateX(0x17, phase17);
    work.setFloat(phase11, 0x21000005);
    work.setFloat(phase17, 0x21000004);
}
void wnWarioBikeStatusUniqProcessUtility::execMapCorrection(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soPostureModule& posture = a->getPostureModule();
    soStatusModule& status = a->getStatusModule();
    soModelModule& model = a->getModelModule();
    soGroundModule& ground = a->getGroundModule();
    // The original performs this cast even though the returned reference is unused.
    dynamic_cast<wnWarioBike&>(a->getStageObject());
    bool wheelie = status.getStatusKind() == 3;
    Vec3f pos = posture.getPos();
    float lr = posture.getLr();
    float angle = work.getFloat(0x21000000);
    float previousAngle = work.getFloat(0x21000001);
    float groundAngle = work.getFloat(0x21000002);
    float difference = 0.017453292f * (angle - previousAngle);
    bool contact17 = false;
    bool contact11 = false;
    float angle11 = groundAngle;
    work.setFloat(angle, 0x21000001);
    work.setFloat(groundAngle, 0x21000003);
    Vec3f rot(-angle, 0.0f, 0.0f);
    posture.setRot(&rot, 0);
    Vec3f node17 = model.getNodeGlobalOffsetFromTop(0x17);
    Vec3f node11 = model.getNodeGlobalOffsetFromTop(0x11);
    Vec3f axis(0.0f, 0.0f, lr);
    Vec3f rotated17;
    Vec3f rotated11;
    // HYPOTHESIS: canonical source argument order remains unresolved for DOL8003DF50.
    node17.rot(&axis, difference, &rotated17);
    node11.rot(&axis, difference, &rotated11);
    Vec3f probe17 = pos + rotated17;
    Vec3f probe11 = pos + rotated11;
    float cosine = fabsf((float)cos(0.017453292f * angle));
    if (fabsf(cosine) < 1.1920929e-7f) cosine = 1.0f;
    float radius17 = 2.4f * a->getPostureModule().getScale();
    float extent17 = radius17 / cosine;
    radius17 = 2.4f * a->getPostureModule().getScale();
    extent17 = (extent17 + radius17) + 0.1f;
    float radius11 = 5.5f * a->getPostureModule().getScale();
    float extent11 = radius11 / cosine;
    radius11 = 5.5f * a->getPostureModule().getScale();
    extent11 = (extent11 + radius11) + 0.1f;
    extent17 += fabsf(rotated17.m_y - node17.m_y);
    extent11 += fabsf(rotated11.m_y - node11.m_y);
    Vec3f down(0.0f, -1000.0f, 0.0f);
    Vec3f hit17;
    Vec3f normal17;
    Vec3f hit11;
    Vec3f normal11;
    probe17.m_y += 2.4f * a->getPostureModule().getScale();
    if (stRayCheck(&probe17, &down, &hit17, &normal17, true, 0, false, 1) && fabsf(hit17.m_y - probe17.m_y) <= extent17) {
        // The first probe's angle calculation has an observable call in the original,
        // but its returned angle is unused; only the second probe updates angle11.
        (void)(float)atan2(-normal17.m_x * lr, normal17.m_y);
        contact17 = true;
    }
    probe11.m_y += 5.5f * a->getPostureModule().getScale();
    if (stRayCheck(&probe11, &down, &hit11, &normal11, true, 0, false, 1) && fabsf(hit11.m_y - probe11.m_y) <= extent11) {
        angle11 = 57.29578f * (float)atan2(-normal11.m_x * lr, normal11.m_y);
        contact11 = true;
    }
    bool touch = ground.isTouch((grCollStatus::TouchMask)8, 0);
    if (touch && !wheelie) {
        if (contact17 && contact11) {
            Vec3f difference = hit17 - hit11;
            groundAngle = 57.29578f * (float)atan2(difference.m_y, fabsf(difference.m_x));
        } else {
            Vec2f normal = ground.getTouchNormal((grCollStatus::TouchMask)8, 0);
            groundAngle = 57.29578f * (float)atan2(-normal.m_x * lr, normal.m_y);
        }
    } else if (contact17 && contact11 && !wheelie) {
        Vec3f difference = hit17 - hit11;
        groundAngle = 57.29578f * (float)atan2(difference.m_y, fabsf(difference.m_x));
    } else if (contact11) {
        groundAngle = angle11;
        pos.m_y = hit11.m_y - rotated11.m_y + 5.5f * a->getPostureModule().getScale();
    } else if (contact17) {
        groundAngle = angle11;
        pos.m_y = hit17.m_y - rotated17.m_y + 2.4f * a->getPostureModule().getScale();
    }
    work.setFloat(angle, 0x21000000);
    work.setFloat(groundAngle, 0x21000002);
    if (wheelie && contact11) posture.setPos(&pos);
    a->getStageObject().updateNodeSRT();
    if (!work.isFlag(0x22000004) && !work.isFlag(0x22000005) && !work.isFlag(0x22000006)) {
        if (contact17 || contact11 || touch) work.onFlag(0x22000002);
    } else if (work.isFlag(0x22000004) || work.isFlag(0x22000005) || work.isFlag(0x22000006)) {
        if (!contact17 && !contact11 && !touch) work.onFlag(0x22000002);
    }
    work.setFlag(contact17, 0x22000004);
    work.setFlag(contact11, 0x22000005);
    work.setFlag(touch, 0x22000006);
}
void wnWarioBikeStatusUniqProcessUtility::execFixPosCounter(soModuleAccesser* a) {
    soWorkManageModule& work = a->getWorkManageModule();
    soEffectModule& effects = a->getEffectModule();
    wnWarioBikeParam* param = dynamic_cast<wnWarioBike&>(a->getStageObject()).m_param;
    float speed = a->getKineticModule().getSumSpeed(soKineticEnergy::AttributeFlag(-1)).length();
    int effectKind = work.getInt(0x20000006);
    int handle = work.getInt(0x20000005);
    if (work.isFlag(0x22000005) || work.isFlag(0x22000004)) {
        if (speed == 0.0f) {
            if (handle >= 0) {
                effects.kill(handle, false, true);
                work.setInt(-1, 0x20000006);
                work.setInt(-1, 0x20000005);
            }
        } else {
            float stick = a->getControllerModule().getStickX();
            if (fabsf(stick) <= 0.5f) {
                if (effectKind != 0x16000e) {
                    if (handle >= 0) effects.kill(handle, false, true);
                    Vec3f rot(0.0f, 0.0f, 0.0f);
                    Vec3f pos(0.0f, 0.0f, 0.0f);
                    handle = effects.reqFollow((EfID)0x16000e, 0x10, &pos, &rot, 1.0f, false, 0, 0, -1);
                    work.setInt(handle, 0x20000005);
                    work.setInt(0x16000e, 0x20000006);
                }
            } else {
                float sign = (float)(stick < 0.0f ? -1 : 1);
                if (sign == a->getPostureModule().getLr() && effectKind != 0x16000b) {
                    if (handle >= 0) effects.kill(handle, false, true);
                    Vec3f rot(0.0f, 0.0f, 0.0f);
                    Vec3f pos(0.0f, 0.0f, 0.0f);
                    handle = effects.reqFollow((EfID)0x16000b, 0x10, &pos, &rot, 1.0f, false, 0, 0, -1);
                    work.setInt(handle, 0x20000005);
                    work.setInt(0x16000b, 0x20000006);
                }
            }
        }
    } else if (handle < 0) {
        Vec3f rot(0.0f, 0.0f, 0.0f);
        Vec3f pos(0.0f, 0.0f, 0.0f);
        handle = effects.reqFollow((EfID)0x16000e, 0x10, &pos, &rot, 1.0f, false, 0, 0, -1);
        work.setInt(handle, 0x20000005);
        work.setInt(0x16000e, 0x20000006);
    }
    if (work.isFlag(0x22000005)) {
        work.incInt(0x20000004);
        if (speed > 0.7f * param->unkC) {
            if (work.getInt(0x20000004) > 10) {
                Vec3f rotRange(0.0f, 0.0f, 0.0f);
                Vec3f posRange(0.0f, 0.0f, 0.0f);
                Vec3f rot(0.0f, 0.0f, 0.0f);
                Vec3f pos(-20.0f, 0.0f, 0.0f);
                effects.req((EfID)0xa, 0, &pos, &rot, 1.0f, &posRange, &rotRange, false, 0);
                work.setInt(0, 0x20000004);
            }
        } else if (speed > 0.3f * param->unkC && work.getInt(0x20000004) > 5) {
            Vec3f rotRange(0.0f, 0.0f, 0.0f);
            Vec3f posRange(0.0f, 0.0f, 0.0f);
            Vec3f rot(0.0f, 0.0f, 0.0f);
            Vec3f pos(-10.0f, 0.0f, 0.0f);
            effects.req((EfID)0x1c, 0, &pos, &rot, 1.0f, &posRange, &rotRange, false, 0);
            work.setInt(0, 0x20000004);
        }
    }
}
void wnWarioBikeStatusUniqProcessUtility::exitStatus(soModuleAccesser* a, int nextStatus) {
    if (nextStatus == 8 || (static_cast<unsigned>(nextStatus) - 0xb <= 2)) {
        int handle = a->getWorkManageModule().getInt(0x20000005);
        if (handle >= 0) {
            a->getEffectModule().kill(handle, true, true);
            a->getWorkManageModule().setInt(-1, 0x20000005);
        }
    }
}
wnWarioBikeStatusUniqProcessUtility g_wnWarioBikeStatusUniqProcessUtility;
