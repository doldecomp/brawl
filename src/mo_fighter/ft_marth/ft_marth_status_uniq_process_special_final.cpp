#include <ft/marth/ft_marth_status_uniq_process.h>
#include <ft/marth/ft_marth.h>
#include <ft/ft_kinetic_energy.h>
#include <gf/gf_task.h>
#include <if/if_marth_final.h>
#include <mt/mt_prng.h>
#include <so/so_module_accesser.h>
#include <so/so_photo_call_back.h>
#include <so/so_value_accesser.h>
#include <math.h>
#include <types.h>

void ftKineticEnergyDisableAndClear(int index, soModuleAccesser* moduleAccesser);

void ftMarthStatusUniqProcessFinal::initStatus(soModuleAccesser* moduleAccesser) {
    ftKineticEnergyDisableAndClear(3, moduleAccesser);
    ftKineticEnergyDisableAndClear(1, moduleAccesser);
    ftKineticEnergyDisableAndClear(2, moduleAccesser);
    ftKineticEnergyDisableAndClear(4, moduleAccesser);
    ftKineticEnergyDisableAndClear(0, moduleAccesser);
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
    case 0x116:
        // Six HP-window slots have independent movement and visibility timers.
        for (int i = 0; i < 6; i++) {
            moduleAccesser->getWorkManageModule().setInt(soValueAccesser::getConstantInt(moduleAccesser, 0x5dc7, 0), 0x2000000a + i);
            moduleAccesser->getWorkManageModule().setInt(soValueAccesser::getConstantInt(moduleAccesser, 0x5dc6, 0), 0x20000010 + i);
            moduleAccesser->getWorkManageModule().setFloat(randi(360), 0x21000004 + i);
        }
        break;
    case 0x11e: {
        ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*moduleAccesser->getKineticModule().getEnergy(3));
        float lr = moduleAccesser->getPostureModule().getLr();
        float factor = soValueAccesser::getConstantFloat(moduleAccesser, 0xfbd, 0);
        factor *= lr;
        float speed = factor;
        if (moduleAccesser->getSituationModule().getKind() == 2) {
            stop.resetEnergy(6, &Vec2f(speed, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
        } else {
            stop.resetEnergy(0, &Vec2f(speed, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
        }
        stop.m_brake = Vec2f(0.0f, 0.0f);
        stop.m_speedLimit = Vec2f(-1.0f, 0.0f);
        stop.enable();
        moduleAccesser->getWorkManageModule().setInt(moduleAccesser->getSituationModule().getKind(), 0x20000003);
        break;
    }
    case 0x120: {
        ftMarth* marth = dynamic_cast<ftMarth*>(&moduleAccesser->getStageObject());
        if (marth != NULL) {
            ((soPhotoCallBack*)((u8*)marth + 0x8554))->addCallback();
        }
        break;
    }
    }
}

// MATCH-ONLY: the original keeps this two-coordinate constructor out of line.
#pragma dont_inline on
static void constructWindowOffset(Vec2f* offset, float x, float y) {
    offset->m_x = x;
    offset->m_y = y;
}
#pragma dont_inline off

void ftMarthStatusUniqProcessFinal::execStatus(soModuleAccesser* moduleAccesser) {
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
    case 0x11e: {
        ftKineticEnergyStop& stop = dynamic_cast<ftKineticEnergyStop&>(*moduleAccesser->getKineticModule().getEnergy(3));
        float lr = moduleAccesser->getPostureModule().getLr();
        float factor = soValueAccesser::getConstantFloat(moduleAccesser, 0xfbd, 0);
        factor *= lr;
        float speed = factor;
        // This routine compares against the saved situation without updating that snapshot.
        if (moduleAccesser->getSituationModule().getKind() != moduleAccesser->getWorkManageModule().getInt(0x20000003)) {
            if (moduleAccesser->getSituationModule().getKind() == 2) {
                stop.resetEnergy(6, &Vec2f(speed, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
            } else {
                stop.resetEnergy(0, &Vec2f(speed, 0.0f), &Vec3f(0.0f, 0.0f, 0.0f), moduleAccesser);
            }
            stop.m_brake = Vec2f(0.0f, 0.0f);
            stop.m_speedLimit = Vec2f(-1.0f, 0.0f);
        } else {
            stop.m_speed = Vec2f(speed, 0.0f);
        }
        break;
    }
    case 0x11f:
        break;
    case 0x120:
        updateHpWindow(moduleAccesser);
        break;
    }
}

void ftMarthStatusUniqProcessFinal::execStop(soModuleAccesser* moduleAccesser) {
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
    case 0x120:
        updateHpWindow(moduleAccesser);
        break;
    }
}

void ftMarthStatusUniqProcessFinal::execFixPos(soModuleAccesser*) {}

void ftMarthStatusUniqProcessFinal::exitStatus(soModuleAccesser* moduleAccesser, int status) {
    switch (moduleAccesser->getStatusModule().getStatusKind()) {
    case 0x120: {
        ftMarth* marth = dynamic_cast<ftMarth*>(&moduleAccesser->getStageObject());
        if (marth == NULL) return;
        ((soPhotoCallBack*)((u8*)marth + 0x8554))->removeCallBack();
        break;
    }
    }
    // Preserve the window tasks between Final Smash phases; delete them on exit.
    switch (status) {
    case 0x11e:
    case 0x11f:
    case 0x120:
        return;
    default: {
        int count = moduleAccesser->getWorkManageModule().getInt(0x20000016);
        for (int i = 0; i < count; i++) {
            gfTask::getTask(moduleAccesser->getWorkManageModule().getInt(0x20000004 + i))->exit();
        }
        break;
    }
    }
}

void ftMarthStatusUniqProcessFinal::updateHpWindow(soModuleAccesser* moduleAccesser) {
    int count = moduleAccesser->getWorkManageModule().getInt(0x20000016);
    if (count > 0) {
        for (int i = 0; i < count; i++) {
            if (moduleAccesser->getWorkManageModule().getInt(0x20000010 + i) > 0) {
                moduleAccesser->getWorkManageModule().subInt(1, 0x20000010 + i);
                // MATCH-ONLY: reserve trig temporaries before the angle to retain register order.
                float y, x;
                // A fixed per-slot angle produces a repeated linear step while its timer runs.
                float angle = moduleAccesser->getWorkManageModule().getFloat(0x21000004 + i);
                float stepSize = soValueAccesser::getConstantFloat(moduleAccesser, 0xfbe, 0);
                y = sin(angle);
                x = cos(angle);
                Vec2f offset;
                constructWindowOffset(&offset, stepSize * x, stepSize * y);
                IfMarthFinalTask* window = dynamic_cast<IfMarthFinalTask*>(gfTask::getTask(moduleAccesser->getWorkManageModule().getInt(0x20000004 + i)));
                if (window != NULL && window->isExecutedCallBack() == 1) {
                    Vec3f position = window->getGlobalPos(0);
                    position.m_x += offset.m_x;
                    position.m_y += offset.m_y;
                    window->setPos(&position, 0);
                }
            }
            if (moduleAccesser->getWorkManageModule().getInt(0x2000000a + i) > 0) {
                moduleAccesser->getWorkManageModule().subInt(1, 0x2000000a + i);
                if (moduleAccesser->getWorkManageModule().getInt(0x2000000a + i) == 0) {
                    IfMarthFinalTask* window = dynamic_cast<IfMarthFinalTask*>(gfTask::getTask(moduleAccesser->getWorkManageModule().getInt(0x20000004 + i)));
                    if (window != NULL) window->dispOff(0);
                }
            }
        }
    }
}

ftMarthStatusUniqProcessFinal g_ftMarthStatusUniqProcessFinal;
