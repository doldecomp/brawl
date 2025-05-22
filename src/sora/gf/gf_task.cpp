#include <gf/gf_task_scheduler.h>
#include <sr/sr_common.h>
#include <gf/gf_task.h>
#include <types.h>

static u32 TaskIdCounter = 1;
static u32 gUnk8059c66c = 0x80000000;

gfTask::gfTask(const char* name, Category category, int unk2, int unk3, bool unk4) {
    unk2C_b6 = true;
    unk2C_b5 = false;
    unk2C_b3 = false;
    unk2C_b2 = true;
    unk2C_b1 = true;
    unk2C_b0 = false;
    m_prev = nullptr;
    m_next = nullptr;
    m_0xC = nullptr;
    m_0x10 = nullptr;
    m_0x14 = nullptr;
    m_0x18 = nullptr;
    m_connectedTask = nullptr;
    m_attachedTask = nullptr;
    m_nextTask = nullptr;
    m_status = 4;
    unk32 = 0xFFFF;
    unk34 = 0;
    unk38 = 0;
    if (srSystemGetDebugLevel() <= 3) {
        unk2C_b3 = true;
    }
    u32 newId = TaskIdCounter++;
    m_taskId = newId;
    m_taskCategory = category;
    m_taskName = name;
    unk30 = unk2;
    unk31 = unk3;
    unk2C_b6 = true;
    gfTaskScheduler::getInstance()->registTask(this);
    if (unk4) {
        m_status = 2;
        if (!unk2C_b0) {
            gfTaskScheduler::getInstance()->link(this);
            unk2C_b0 = true;
        }
    } else {
        m_status = 4;
    }
}

gfTask::~gfTask() {
    if (UnkClass* curr = unk38) {
        curr->func();
        curr = curr->m_next;
        while (curr) {
            curr->func();
            curr = curr->m_next;
        }
    }
    if (gfTaskScheduler::getInstance()->isRegist(this)) {
        m_status = 3;
        if (unk2C_b0) {
            gfTaskScheduler::getInstance()->unlink(this);
        }
        gfTaskScheduler::getInstance()->removeFromSuspendList(this);
    }
    m_status = 5;
}

void gfTask::updateId() {
    u32 newId = gUnk8059c66c++ | 0x80000000;
    m_taskId = newId;
}

void gfTask::link(bool p1) {
    if (!unk2C_b0) {
        gfTaskScheduler::getInstance()->link(this);
        unk2C_b0 = true;
        if (p1) {
            m_status = 1;
        }
    }
}

void gfTask::unlink() {
    if (unk2C_b0) {
        gfTaskScheduler::getInstance()->unlink(this);
        gfTaskScheduler::getInstance()->unregistTask(this);
        m_0xC = nullptr;
        m_0x10 = nullptr;
        m_0x14 = nullptr;
        m_0x18 = nullptr;
        unk2C_b0 = false;
    }
}

void gfTask::setPaused(bool paused) {
    if (paused) {
        unk34 = 0x8000;
    } else {
        unk34 &= 0x7FFF;
    }
}

gfTask* gfTask::getTask(int taskId) {
    return gfTaskScheduler::getInstance()->getTask(taskId);
}

void gfTask::process(TaskType taskType) {
    if (taskType < 8) {
        switch (taskType) {
            case Task_Default:
                processDefault();
                break;
            case Task_Begin:
                processBegin();
                break;
            case Task_Anim:
                processAnim();
                break;
            case Task_Update:
                processUpdate();
                break;
            case Task_PreMapCorrection:
                processPreMapCorrection();
                break;
            case Task_MapCorrection:
                processMapCorrection();
                break;
            case Task_FixPosition:
                processFixPosition();
                break;
            case Task_PreCollision:
                processPreCollision();
                break;
            default:
                break;
        }
    } else {
        switch (taskType) {
            case Task_Collision:
                processCollision();
                break;
            case Task_Catch:
                processCatch();
                break;
            case Task_Hit:
                processHit();
                break;
            case Task_Camera:
                processCamera();
                break;
            case Task_FixCamera:
                processFixCamera();
                break;
            case Task_Effect:
                processEffect();
                break;
            case Task_GameProc:
                processGameProc();
                break;
            case Task_End:
                processEnd();
                break;
            default:
                break;
        }
    }
}

void gfTask::init() { }

void gfTask::processDefault() {
    unk32 &= ~(1 << Task_Default);
}

void gfTask::processBegin() {
    unk32 &= ~(1 << Task_Begin);
}

void gfTask::processAnim() {
    unk32 &= ~(1 << Task_Anim);
}

void gfTask::processUpdate() {
    unk32 &= ~(1 << Task_Update);
}

void gfTask::processPreMapCorrection() {
    unk32 &= ~(1 << Task_PreMapCorrection);
}

void gfTask::processMapCorrection() {
    unk32 &= ~(1 << Task_MapCorrection);
}

void gfTask::processFixPosition() {
    unk32 &= ~(1 << Task_FixPosition);
}

void gfTask::processPreCollision() {
    unk32 &= ~(1 << Task_PreCollision);
}

void gfTask::processCollision() {
    unk32 &= ~(1 << Task_Collision);
}

void gfTask::processCatch() {
    unk32 &= ~(1 << Task_Catch);
}

void gfTask::processHit() {
    unk32 &= ~(1 << Task_Hit);
}

void gfTask::processCamera() {
    unk32 &= ~(1 << Task_Camera);
}

void gfTask::processFixCamera() {
    unk32 &= ~(1 << Task_FixCamera);
}

void gfTask::processEffect() {
    unk32 &= ~(1 << Task_Effect);
}

void gfTask::processGameProc() {
    unk32 &= ~(1 << Task_GameProc);
}

void gfTask::processEnd() {
    unk32 &= ~(1 << Task_End);
}

void gfTask::renderPre() { }

void gfTask::renderOpa() { }

void gfTask::renderXlu() { }

void gfTask::processDebug() { }

void gfTask::renderDebug() { }

void gfTask::render(Render kind) {
    switch (kind) {
        case Render_Pre:
            renderPre();
            break;
        case Render_Opa:
            renderOpa();
            break;
        case Render_Xlu:
            renderXlu();
            break;
    }
}

void gfTask::exit() {
    if (m_status != 3) {
        m_status = 3;
        unk2C_b6 = false;
        gfTask* r31 = m_attachedTask;
        while (r31) {
            if (r31->m_status != 3) {
                r31->m_status = 3;
                r31->unk2C_b6 = false;

                gfTask* r29 = r31->m_attachedTask;
                while (r29) {
                    if (r29->m_status != 3) {
                        r29->m_status = 3;
                        r29->unk2C_b6 = false;

                        gfTask* r28 = r29->m_attachedTask;
                        while (r28) {
                            r28->exit();
                            r28 = r28->m_nextTask;
                        }
                        if (gfTaskScheduler::getInstance()->getUnk0_1() == 4) {
                            gfTaskScheduler::getInstance()->setUnk2_7();
                        }
                    }
                    r29 = r29->m_nextTask;
                }
                if (gfTaskScheduler::getInstance()->getUnk0_1() == 4) {
                    gfTaskScheduler::getInstance()->setUnk2_7();
                }
            }
            r31 = r31->m_nextTask;
        }
        if (gfTaskScheduler::getInstance()->getUnk0_1() == 4) {
            gfTaskScheduler::getInstance()->setUnk2_7();
        }
    }
}
