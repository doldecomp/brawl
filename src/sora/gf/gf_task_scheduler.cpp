#include <StaticAssert.h>
#include <cstring>
#include <gf/gf_task.h>
#include <gf/gf_task_scheduler.h>
#include <sr/sr_common.h>
#include <types.h>

gfTaskScheduler* g_taskScheduler;

#define TASKLIST_APPEND(head, task, prev, next) \
    do {                                        \
        gfTask* currNode = (head);              \
        if (!currNode) {                        \
            (head) = (task);                    \
        } else {                                \
            while (currNode->next) {            \
                currNode = currNode->next;      \
            }                                   \
            currNode->next = (task);            \
            (task)->prev = currNode;            \
        }                                       \
    } while (false)

#define TASKLIST_PREPEND(head, task, prev, next)    \
    if (!(head)) {                                  \
        (head) = (task);                            \
        (task)->prev = nullptr;                     \
        (task)->next = nullptr;                     \
    } else {                                        \
        gfTask* oldHead = (head);                   \
        (task)->next = (head);                      \
        (head) = (task);                            \
        task->prev = nullptr;                       \
        oldHead->prev = (task);                     \
    }

#define TASKLIST_REMOVE(head, task, prevPtr, nextPtr, prev, next) \
    do {                                                          \
        if ((head) == (task)) {                                   \
            (head) = (nextPtr);                                   \
            if (nextPtr) {                                        \
                (nextPtr)->prev = nullptr;                        \
            }                                                     \
        } else {                                                  \
            (prevPtr) = (task)->prev;                             \
            if (prevPtr) {                                        \
                (prevPtr)->next = (nextPtr);                      \
            }                                                     \
            if (nextPtr) {                                        \
                (nextPtr)->prev = (prevPtr);                      \
            }                                                     \
        }                                                         \
    } while (false)

gfTaskScheduler* gfTaskScheduler::create() {
    return (g_taskScheduler = new (Heaps::SystemFW) gfTaskScheduler);
}

gfTaskScheduler* gfTaskScheduler::getInstance() {
    return g_taskScheduler;
}

void gfTaskScheduler::clear() {
    m_numRegisteredTasks = 0;
    unk8 = nullptr;
    unkC = nullptr;
    unk10 = nullptr;
    m_suspendList = nullptr;
    for (s32 i = 0; i < unk14Size; i++) {
        unk14[i] = nullptr;
    }
    for (s32 i = 0; i < unk58Size; i++) {
        unk58[i] = nullptr;
    }
    for (s32 i = 0; i < unkF8Size; i++) {
        unkF8[i] = nullptr;
    }
}

void gfTaskScheduler::updateStatusPre() {
    for (s32 i = 0; i < unk58Size; i++) {
        for (gfTask* curr = unk58[i]; curr; curr = curr->m_0x10) {
            curr->unk2C_b5 = curr->unk34;
        }
    }
    gfTask* next;
    for (gfTask* curr = m_suspendList; curr; curr = next) {
        next = curr->m_next;
        curr->unk2C_b5 = curr->unk34;
    }
}

// NONMATCHING regswaps
void gfTaskScheduler::process(bool p1) {
    u32 count;
    gfTask* r26;
    gfTask* curr;
    gfTask* r24;
    UnkTaskRequest* r31;
    gfTask** r30;
    s32 i;
    updateStatusPre();
    unk0_1 = 1;
    // loop over TaskTypes?
    for (i = 0; i < 0x10; i++) {
        unk0_2 = i;
        // UBFIX: logic depends on shift overflow?
        if (!unk8 || !(1 << i)) {
            r30 = unk14;
            // loop over task priority levels?
            for (s32 j = 0; j < unk14Size; j++, r30++) {
                curr = *r30;
                unk6 = j;
                while (curr) {
                    r24 = curr->m_prev;
                    gfTask* next = curr->m_next;
                    unkC = curr;
                    unk10 = next;
                    if (p1) {
                        if (curr->unk2C_b6 && !curr->unk2C_b5) {
                            curr->process(static_cast<gfTask::TaskType>(i));
                        }
                    } else {
                        if (curr->unk2C_b6 && !curr->getFlag1()) {
                             curr->process(static_cast<gfTask::TaskType>(i));
                        }
                    }
                    if (!curr->unk2C_b0) {
                        if (!r24) {
                            curr = *r30;
                        } else {
                            curr = unk10;
                        }
                    } else {
                        curr = curr->m_next;
                    }
                }
            }
        }
    }

    unkC = nullptr;
    unk10 = nullptr;

    // Process priority change requests?
    count = m_numPendingPrioUpdates;
    if (count) {
        r31 = m_pendingPrioUpdates;
        for (i = 0; i < count; r31++, i++) {
            r26 = getTaskById(r31->m_category, r31->m_taskId);
            if (r26) {
                if (!r26->unk2C_b0) {
                    r31->m_task->unk30 = r31->m_priority;
                } else {
                    unlinkProcessList(r26);
                    r26->unk30 = r31->m_priority;
                    TASKLIST_APPEND(unk14[r26->unk30], r26, m_prev, m_next);
                }
            }
        }
        m_numPendingPrioUpdates = 0;
    }
    unk0_1 = 0;
}

// NONMATCHING regswaps
void gfTaskScheduler::renderPre() {
    gfTask* next;
    gfTask* r3;
    unk0_1 = 2;
    for (s32 i = 0; i < unkF8Size; i++) {
        r3 = unkF8[i];
        unk6 = i;
        for (gfTask* task = r3; task; task = next) {
            next = task->m_0x18;
            if (task->unk2C_b6 && task->unk2C_b2) {
                task->renderPre();
            }
        }
    }
}

// NONMATCHING regswaps
void gfTaskScheduler::render() {
    unk0_1 = 2;
    gfTask* r31;
    gfTask* r3;
    for (s32 i = 0; i < unkF8Size; i++) {
        r3 = unkF8[i];
        unk6 = i;
        for (gfTask* task = r3; task; task = r31) {
            r31 = task->m_0x18;
            if (task->unk2C_b6 && task->unk2C_b2) {
                task->render(gfTask::Render_Opa);
            }
        }
    }
    for (s32 i = 0; i < unkF8Size; i++) {
        r3 = unkF8[i];
        unk6 = i;
        for (gfTask* task = r3; task; task = r31) {
            r31 = task->m_0x18;
            if (task->unk2C_b6 && task->unk2C_b2) {
                task->render(gfTask::Render_Xlu);
            }
        }
    }
    unk0_1 = 0;
}

// NONMATCHING regswaps
void gfTaskScheduler::updateStatus() {
    unk0_1 = 4;
    do {
        gfTask* next;
        unk2_b7 = false;
        for (s32 i = 0; i < unk14Size; i++) {
            for (gfTask* curr = unk14[i]; curr; curr = next) {
                next = curr->m_next;
                if (curr->unk2C_b6 && curr->getStatus() == 2) {
                    curr->setStatus(1);
                }
                if (curr->getStatus() == 3) {
                    curr->unlink();
                    removeFromSuspendList(curr);
                    m_numRegisteredTasks--;
                    delete curr;
                }
            }
        }
        for (gfTask* curr = m_suspendList; curr; curr = next) {
            next = curr->m_next;
            if (curr->getStatus() == 3) {
                removeFromSuspendList(curr);
                m_numRegisteredTasks--;
                delete curr;
            }
        }
    } while (unk2_b7 == true);
    unk0_1 = 0;
}

void gfTaskScheduler::removeFromSuspendList(gfTask* task) {
    gfTask* prev = task->m_prev;
    gfTask* next = task->m_next;
    TASKLIST_REMOVE(m_suspendList, task, prev, next, m_prev, m_next);
    task->m_prev = nullptr;
    task->m_next = nullptr;
}

void gfTaskScheduler::unlinkProcessList(gfTask* task) {
    gfTask* prev = task->m_prev;
    gfTask* next = task->m_next;
    if (unkC == task) {
        unk10 = task->m_next;
    }
    if (unk10 == task) {
        unk10 = task->m_next;
    }
    TASKLIST_REMOVE(unk14[task->unk30], task, prev, next, m_prev, m_next);
    task->m_prev = nullptr;
    task->m_next = nullptr;
}

void gfTaskScheduler::unlink(gfTask* task) {
    unlinkProcessList(task);
    gfTask* prev;
    gfTask* next = task->m_0x10;
    TASKLIST_REMOVE(unk58[task->m_taskCategory], task, prev, next, m_0xC, m_0x10);

    next = task->m_0x18;
    TASKLIST_REMOVE(unkF8[task->unk31], task, prev, next, m_0x14, m_0x18);

    task->setStatus(4);
    TASKLIST_PREPEND(m_suspendList, task, m_prev, m_next);
}

void gfTaskScheduler::link(gfTask* task) {
    removeFromSuspendList(task);
    TASKLIST_APPEND(unk14[task->unk30], task, m_prev, m_next);
    TASKLIST_APPEND(unk58[task->m_taskCategory], task, m_0xC, m_0x10);
    TASKLIST_APPEND(unkF8[task->unk31], task, m_0x14, m_0x18);
    if (unk0_1) {
        task->setStatus(2);
    } else {
        task->setStatus(1);
    }
}

void gfTaskScheduler::registTask(gfTask* task) {
    m_numRegisteredTasks++;
    TASKLIST_PREPEND(m_suspendList, task, m_prev, m_next);
}

bool gfTaskScheduler::isRegist(const gfTask* task) const {
    bool result = false;
    for (gfTask* curr = unk14[task->unk30]; curr; curr = curr->m_next) {
        if (curr == task) {
            result = true;
            break;
        }
    }
    if (!result) {
        for (gfTask* curr = m_suspendList; curr; curr = curr->m_next) {
            if (curr == task) {
                result = true;
                break;
            }
        }
    }
    return result;
}

gfTask* gfTaskScheduler::getTask(const char* name) {
    for (s32 i = 0; i < unk14Size; i++) {
        for (gfTask* curr = unk14[i]; curr; curr = curr->m_next) {
            if (!strcmp(curr->m_taskName, name)) {
                return curr;
            }
        }
    }
    return nullptr;
}

gfTask* gfTaskScheduler::getTask(u32 id) {
    for (s32 i = 0; i < unk14Size; i++) {
        for (gfTask* curr = unk14[i]; curr; curr = curr->m_next) {
            if (id == curr->m_taskId) {
                return curr;
            }
        }
    }
    return nullptr;
}

gfTask* gfTaskScheduler::getTask(gfTask::Category ctgry, u32 pos) {
    for (gfTask* curr = unk58[ctgry]; curr; curr = curr->m_0x10) {
        if (pos == 0) {
            return curr;
        }
        pos--;
    }
    return nullptr;
}

gfTask* gfTaskScheduler::getTaskById(gfTask::Category ctgry, u32 id) {
    for (gfTask* curr = unk58[ctgry]; curr; curr = curr->m_0x10) {
        if (id == curr->m_taskId) {
            return curr;
        }
    }
    return nullptr;
}

void gfTaskScheduler::setPauseCategory(gfTask::Category ctgry, bool isPaused) {
    for (gfTask* curr = unk58[ctgry]; curr; curr = curr->m_0x10) {
        curr->setPaused(isPaused);
    }
    for (gfTask* curr = m_suspendList; curr; curr = curr->m_next) {
        if (ctgry == curr->m_taskCategory) {
            curr->setPaused(isPaused);
        }
    }
}

// NONMATCHING regswaps, instruction order, dead store
void gfTaskScheduler::changeTaskPriorityRequest(u32 id, u8 priority) {
    gfTask* task = getTask(id);
    if (task) {
        UnkTaskRequest x(false);
        x.m_category = task->m_taskCategory;
        x.m_taskId = task->m_taskId;
        x.m_priority = priority;
        m_pendingPrioUpdates[m_numPendingPrioUpdates] = x;
        m_numPendingPrioUpdates++;
    }
}
