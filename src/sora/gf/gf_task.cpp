#include <gf/gf_callback.h>
#include <gf/gf_task_scheduler.h>
#include <sr/sr_common.h>
#include <gf/gf_task.h>
#include <types.h>

static u32 TaskIdCounter = 1;
static u32 gUnk8059c66c = 0x80000000;

gfTask::gfTask(const char* name, Category category, int unk2, int unk3, bool unk4) {
    m_alive = true;
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
    unk32 = ~0;
    unk34 = 0;
    unk38.m_head = nullptr;
    if (srSystemGetDebugLevel() <= 3) {
        unk2C_b3 = true;
    }
    u32 newId = TaskIdCounter++;
    m_taskId = newId;
    m_taskCategory = category;
    m_taskName = name;
    unk30 = unk2;
    unk31 = unk3;
    m_alive = true;
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
    if (gfCallBack* curr = unk38.m_head) {
        curr->userProc();
        curr = curr->m_next;
        while (curr) {
            curr->userProc();
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

void gfTask::process(ProcessType taskType) {
    if (taskType < 8) {
        switch (taskType) {
            case Process_Default:
                processDefault();
                break;
            case Process_Begin:
                processBegin();
                break;
            case Process_Anim:
                processAnim();
                break;
            case Process_Update:
                processUpdate();
                break;
            case Process_PreMapCorrection:
                processPreMapCorrection();
                break;
            case Process_MapCorrection:
                processMapCorrection();
                break;
            case Process_FixPosition:
                processFixPosition();
                break;
            case Process_PreCollision:
                processPreCollision();
                break;
            default:
                break;
        }
    } else {
        switch (taskType) {
            case Process_Collision:
                processCollision();
                break;
            case Process_Catch:
                processCatch();
                break;
            case Process_Hit:
                processHit();
                break;
            case Process_Camera:
                processCamera();
                break;
            case Process_FixCamera:
                processFixCamera();
                break;
            case Process_Effect:
                processEffect();
                break;
            case Process_GameProc:
                processGameProc();
                break;
            case Process_End:
                processEnd();
                break;
            default:
                break;
        }
    }
}

void gfTask::init() { }

void gfTask::processDefault() {
    unk32 &= ~(1 << Process_Default);
}

void gfTask::processBegin() {
    unk32 &= ~(1 << Process_Begin);
}

void gfTask::processAnim() {
    unk32 &= ~(1 << Process_Anim);
}

void gfTask::processUpdate() {
    unk32 &= ~(1 << Process_Update);
}

void gfTask::processPreMapCorrection() {
    unk32 &= ~(1 << Process_PreMapCorrection);
}

void gfTask::processMapCorrection() {
    unk32 &= ~(1 << Process_MapCorrection);
}

void gfTask::processFixPosition() {
    unk32 &= ~(1 << Process_FixPosition);
}

void gfTask::processPreCollision() {
    unk32 &= ~(1 << Process_PreCollision);
}

void gfTask::processCollision() {
    unk32 &= ~(1 << Process_Collision);
}

void gfTask::processCatch() {
    unk32 &= ~(1 << Process_Catch);
}

void gfTask::processHit() {
    unk32 &= ~(1 << Process_Hit);
}

void gfTask::processCamera() {
    unk32 &= ~(1 << Process_Camera);
}

void gfTask::processFixCamera() {
    unk32 &= ~(1 << Process_FixCamera);
}

void gfTask::processEffect() {
    unk32 &= ~(1 << Process_Effect);
}

void gfTask::processGameProc() {
    unk32 &= ~(1 << Process_GameProc);
}

void gfTask::processEnd() {
    unk32 &= ~(1 << Process_End);
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
        m_alive = false;
        for (gfTask* c = m_attachedTask; c; c = c->m_nextTask) {
            c->exit();
        }
        if (gfTaskScheduler::getInstance()->getUnk0_1() == 4) {
            gfTaskScheduler::getInstance()->setUnk2_7();
        }
    }
}
