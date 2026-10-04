#include <gf/gf_task.h>
#include <gf/gf_task_scheduler.h>
#include <so/so_module_accesser.h>
#include <so/stageobject.h>
#include <so/status/so_status_module_impl.h>
#include <types.h>

int soStatusModuleImpl::getStatusKind() {
    return m_statusKind;
}

bool soStatusModuleImpl::isObserv(char unk1) {
    return unk1 == 2;
}

char* soStatusModuleImpl::getStatusName() {
    return "UNKNOWN";
}

char* soStatusModuleImpl::getStatusName(int status) {
    if (status == -1) {
        return "None";
    }
    if (status < 0 || status >= m_statusDataArr->size()) {
        return "Error!";
    }
    return "UNKNOWN";
}

u32 soStatusModuleImpl::getStatusGroundCorrect(int status) {
    if (status == -1) {
        status = m_statusKind;
    }
    if (status < 0 || status >= m_statusDataArr->size()) {
        return 0;
    }
    // HYPOTHESIS: soStatusData has a 4 bit ground-correct field in the top nibble-pair of the word at +0xC.
    const soStatusData& data = m_statusDataArr->at(status);
    return (*(const u32*)((const char*)&data + 0xC) >> 24) & 0xF;
}

void soStatusModuleImpl::addRangeUniqProc(soStatusUniqProcess** uniqProcs, u32 numUniqProcs) {
    if (uniqProcs != 0) {
        for (s32 i = 0; i < (s32)numUniqProcs; i++) {
            m_statusUniqProcessArr->push(uniqProcs[i]);
        }
    }
}

void soStatusModuleImpl::begin() {
    m_unk7c = false;
}

int soStatusModuleImpl::getPrevStatusKind(u32 index) {
    if (index >= (*m_statusHistory)->size() || (*m_statusHistory)->size() <= 0) {
        return -1;
    }
    return (*m_statusHistory)->at(index);
}

void soStatusModuleImpl::setUniqProc(u32 index, soStatusUniqProcess* uniqProc) {
    m_statusUniqProcessArr->at(index) = uniqProc;
}

void soStatusModuleImpl::unableTransitionTerm(int a, int b) {
    m_transitionModule->unableTerm(a, b);
}

void* soStatusModuleImpl::getLastStatusTransitionInfo() {
    return m_transitionModule->getLastTransitionInfo();
}

void soStatusModuleImpl::clearTransitionTermAll(int groupID) {
    m_transitionModule->clearTransitionTermAll(groupID);
}

void soStatusModuleImpl::enableTransitionTermAll(int groupID) {
    m_transitionModule->enableTermAll(groupID);
}

bool soStatusModuleImpl::isEnableTransitionTermGroup(int groupID) {
    return m_transitionModule->isEnableTermGroup(groupID);
}

void soStatusModuleImpl::unableTransitionTermGroup(int groupID) {
    m_transitionModule->unableTermGroup(groupID);
}

void soStatusModuleImpl::enableTransitionTermGroup(int groupID) {
    m_transitionModule->enableTermGroup(groupID);
}

bool soStatusModuleImpl::isChanged() {
    return m_isChanged;
}

void soStatusModuleImpl::startWatchChange() {
    m_isChanged = false;
}

bool soStatusModuleImpl::isCollisionAttackOccer() {
    return m_isCollisionAttackOccer;
}

// HYPOTHESIS: soStatusData starts with three masks selecting which flag/int/float work values survive a status change.
void soStatusModuleImpl::succeedStatusWork(const soStatusData* statusData) {
    const u32* masks = (const u32*)statusData;
    if (masks[0] == 0 && masks[1] == 0 && masks[2] == 0) {
        m_generalWork->clearWorkAll();
        return;
    }
    s32 intNum = m_generalWork->getIntWorkSize();
    if (intNum > 31) {
        intNum = 31;
    }
    for (s32 i = 0; i < intNum; i++) {
        if ((masks[1] & (1 << i)) == 0) {
            m_generalWork->setIntWork(0, i);
        }
    }
    s32 floatNum = m_generalWork->getFloatWorkSize();
    if (floatNum > 31) {
        floatNum = 31;
    }
    for (s32 i = 0; i < floatNum; i++) {
        if ((masks[2] & (1 << i)) == 0) {
            m_generalWork->setFloatWork(0.0f, i);
        }
    }
    s32 flagNum = m_generalWork->getFlagWorkSize();
    if (flagNum > 0) {
        m_generalWork->offFlag(~masks[0], 0);
        for (s32 i = 1; i < flagNum; i++) {
            m_generalWork->clearFlag(i);
        }
    }
}

// HYPOTHESIS: m_unk7d is set once the module is active (guards the per-frame exec* callbacks).
#define SO_STATUS_EXEC(name, slot)     void soStatusModuleImpl::name(soModuleAccesser* moduleAccesser) {         if (m_unk7d == true) {             int status = m_statusKind;             if (status >= 0 && status < m_statusUniqProcessArr->size()) {                 soStatusUniqProcess* proc = m_statusUniqProcessArr->at(status);                 if (proc != 0) {                     proc->slot(moduleAccesser);                 }             }         }     }

SO_STATUS_EXEC(execStatus, execStatus)
SO_STATUS_EXEC(execStop, execStop)
SO_STATUS_EXEC(execMapCorrection, execMapCorrection)
SO_STATUS_EXEC(execFixPosCounter, execFixPosCounter)
SO_STATUS_EXEC(execFixPos, execFixPos)
SO_STATUS_EXEC(execFixCamera, execFixCamera)

bool soStatusModuleImpl::checkDamage(soModuleAccesser* moduleAccesser, void* arg) {
    int status = m_statusKind;
    if (status >= 0 && status < m_statusUniqProcessArr->size()) {
        soStatusUniqProcess* proc = m_statusUniqProcessArr->at(status);
        if (proc != 0) {
            if (proc->checkDamage(moduleAccesser, arg) == true) {
                return true;
            }
        }
    }
    return false;
}

void soStatusModuleImpl::checkAttack(soModuleAccesser* moduleAccesser, void* arg, float power) {
    int status = m_statusKind;
    if (status >= 0 && status < m_statusUniqProcessArr->size()) {
        soStatusUniqProcess* proc = m_statusUniqProcessArr->at(status);
        if (proc != 0) {
            proc->checkAttack(moduleAccesser, arg, power);
        }
    }
}

bool soStatusModuleImpl::onChangeLr(soModuleAccesser* moduleAccesser, float prevLr, float lr) {
    int status = m_statusKind;
    if (status >= 0 && status < m_statusUniqProcessArr->size()) {
        soStatusUniqProcess* proc = m_statusUniqProcessArr->at(status);
        if (proc != 0) {
            if (proc->onChangeLr(moduleAccesser, prevLr, lr) == true) {
                return true;
            }
        }
    }
    return false;
}

void soStatusModuleImpl::leaveStop(soModuleAccesser* moduleAccesser, int a, bool b) {
    int status = m_statusKind;
    if (status >= 0 && status < m_statusUniqProcessArr->size()) {
        soStatusUniqProcess* proc = m_statusUniqProcessArr->at(status);
        if (proc != 0) {
            proc->leaveStop(moduleAccesser, a, b);
        }
    }
}

void soStatusModuleImpl::activate(soModuleAccesser* moduleAccesser) {
    (*m_statusHistory)->clear();
    m_transitionModule->clearTransitionTermAll(0);
    changeStatusForce(-1, moduleAccesser);
    m_changeRequestQueue.clear();
}

void soStatusModuleImpl::deactivate(soModuleAccesser* moduleAccesser) {
    (*m_statusHistory)->clear();
    m_transitionModule->clearTransitionTermAll(0);
    changeStatusForce(-1, moduleAccesser);
}

void soStatusModuleImpl::notifyEventCollisionAttack(float power, soCollisionLog* collisionLog, soModuleAccesser* moduleAccesser) {
    m_isCollisionAttackOccer = true;
    m_collisionLog.m_taskId = -1;
    if (collisionLog != 0) {
        m_collisionLog = *(soStatusCollisionLogCopy*)collisionLog;
    }
}

bool soStatusModuleImpl::isCollisionAttackTarget(u32* collisionAttackCategory) {
    if (!m_isCollisionAttackOccer || m_collisionLog.m_taskId == (u32)-1) {
        return false;
    }
    gfTaskScheduler* scheduler = gfTaskScheduler::getInstance();
    if (scheduler == 0) {
        return false;
    }
    gfTask* task = scheduler->getTaskById((gfTask::Category)m_collisionLog.m_taskCategory, m_collisionLog.m_taskId);
    StageObject* stageObject = dynamic_cast<StageObject*>(task);
    if (stageObject == 0) {
        return false;
    }
    return (*collisionAttackCategory & (1 << stageObject->soGetKind())) != 0;
}

void soStatusModuleImpl::connectStatusDataList(void* list) {
    m_statusDataArr->connect((soArrayContractibleTable<const soStatusData>*)list);
}


// MATCH-ONLY: view of the soAnimCmdModule vtable that exposes the slot at +0x28, used to run the
// pre-check anim cmd of a status. The real name/signature are unknown (BrawlHeaders mislabels this
// part of the soAnimCmdModule vtable).
// HYPOTHESIS: 4 byte aligned flag object whose first member is a u16 mask.
union AnimCmdPreCheckFlag {
    u16 m_mask;
    u32 m_pad;
};

class soAnimCmdModulePreCheckView {
public:
    virtual void unk08();
    virtual void unk0c();
    virtual void interpretCmd(soModuleAccesser* moduleAccesser, u16* flag, float frame); // +0x10 (HYPOTHESIS signature)
    virtual void unk14();
    virtual void unk18();
    virtual void unk1c();
    virtual void unk20();
    virtual void unk24();
    virtual void preCheck(u16* flag, void* cmd, soModuleAccesser* moduleAccesser, int a, int b);
};

static inline void callAnimCmdInterpret(soAnimCmdModule& module, soModuleAccesser* acc, u16* flag, float frame) {
    ((soAnimCmdModulePreCheckView&)module).interpretCmd(acc, flag, frame);
}

static inline void callAnimCmdPreCheck(soAnimCmdModule& module, u16* flag, void* cmd, soModuleAccesser* acc, int a, int b) {
    ((soAnimCmdModulePreCheckView&)module).preCheck(flag, cmd, acc, a, b);
}

static inline soLockable& getWorkLock(soModuleAccesser* moduleAccesser) {
    return static_cast<soLockable&>(static_cast<soWorkManageModuleImpl&>(moduleAccesser->getWorkManageModule()));
}

// Common body of changeStatusRequest / changeStatusForce.
static inline void changeStatusSub(soStatusModuleImpl* self, int status, soModuleAccesser* moduleAccesser) {
    if (moduleAccesser->getStageObject().checkTransitionStatus(status)) {
        getWorkLock(moduleAccesser).lock();
        self->m_nextStatusKind = status;
        if (self->m_preCheckAnimCmdArr != 0 && status > -1 && status < self->m_preCheckAnimCmdNum
            && self->m_preCheckAnimCmdArr[status] != 0) {
            AnimCmdPreCheckFlag flag;
            flag.m_mask = 1;
            callAnimCmdPreCheck(moduleAccesser->getAnimCmdModule(), &flag.m_mask, self->m_preCheckAnimCmdArr[status], moduleAccesser, 1, 0);
        }
        self->changeStatus(self->m_nextStatusKind, moduleAccesser);
        getWorkLock(moduleAccesser).unlock();
    }
}

// HYPOTHESIS: mirror of the leading bitfields of gfTaskScheduler (the header's view is private/offset differs).
struct gfTaskSchedulerPhaseView {
    u32 unk0_1 : 8;
    s32 phase : 8;
};

bool soStatusModuleImpl::changeStatusRequest(int status, soModuleAccesser* moduleAccesser) {
    // MATCH-ONLY: keeps the requested status memory-resident like the original.
    gfTaskScheduler* scheduler = gfTaskScheduler::getInstance();
    if (scheduler != 0 && (((gfTaskSchedulerPhaseView*)scheduler)->phase <= 1 || ((gfTaskSchedulerPhaseView*)scheduler)->phase >= 6)) {
        if (m_changeRequestQueue.isEmpty() != true) {
            while (m_changeRequestQueue.isEmpty() == false) {
                int next = m_changeRequestQueue.at(0);
                m_changeRequestQueue.shift();
                changeStatusSub(this, next, moduleAccesser);
            }
        }
        m_unk7c = true;
        changeStatusSub(this, (&status)[0], moduleAccesser);
        return true;
    }
    if (m_changeRequestQueue.isFull() != true) {
        m_changeRequestQueue.push((const s32&)(&status)[0]);
    }
    return false;
}

void soStatusModuleImpl::processFixPosition(soModuleAccesser* moduleAccesser, bool unk) {
    if (unk == true) {
        AnimCmdPreCheckFlag flag;
        flag.m_mask = 1;
        callAnimCmdInterpret(moduleAccesser->getAnimCmdModule(), moduleAccesser, &flag.m_mask, 0.0f);
        return;
    }
    bool processed;
    if (m_changeRequestQueue.isEmpty() == true) {
        processed = false;
    } else {
        while (m_changeRequestQueue.isEmpty() == false) {
            int next = m_changeRequestQueue.at(0);
            m_changeRequestQueue.shift();
            changeStatusSub(this, next, moduleAccesser);
        }
        processed = true;
    }
    if (processed == false && m_unk7c == false) {
        if (moduleAccesser->getStopModule().isStop() == false) {
            AnimCmdPreCheckFlag flag;
            flag.m_mask = 0x1d;
            callAnimCmdInterpret(moduleAccesser->getAnimCmdModule(), moduleAccesser, &flag.m_mask, 1.0f);
        } else {
            AnimCmdPreCheckFlag flag;
            flag.m_mask = 0x10;
            callAnimCmdInterpret(moduleAccesser->getAnimCmdModule(), moduleAccesser, &flag.m_mask, 1.0f);
        }
    }
}

void soStatusModuleImpl::changeStatusForce(int status, soModuleAccesser* moduleAccesser) {
    changeStatusSub(this, status, moduleAccesser);
}

template class soArrayVector<s32, 8>;
template class soArrayVectorAbstract<s32>;
template class soArray<s32>;
template class soArrayContractible<s32>;
template class soArrayFixed<s32>;
