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
        m_collisionLog = *collisionLog;
    }
}

bool soStatusModuleImpl::isCollisionAttackTarget(u32* collisionAttackCategory) {
    if (!m_isCollisionAttackOccer || m_collisionLog.m_taskId == -1) {
        return false;
    }
    gfTaskScheduler* scheduler = gfTaskScheduler::getInstance();
    if (scheduler == 0) {
        return false;
    }
    gfTask* task = scheduler->getTaskById(m_collisionLog.m_taskCategory, m_collisionLog.m_taskId);
    StageObject* stageObject = dynamic_cast<StageObject*>(task);
    if (stageObject == 0) {
        return false;
    }
    return (*collisionAttackCategory & (1 << stageObject->soGetKind())) != 0;
}

void soStatusModuleImpl::connectStatusDataList(void* list) {
    m_statusDataArr->connect((soArrayContractibleTable<const soStatusData>*)list);
}

template class soArrayVector<s32, 8>;
template class soArrayVectorAbstract<s32>;
template class soArray<s32>;
template class soArrayContractible<s32>;
template class soArrayFixed<s32>;
