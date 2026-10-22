#pragma once

#include <StaticAssert.h>
#include <gf/gf_task.h>
#include <types.h>

// TODO: Task priority request record?
struct UnkTaskRequest {
    gfTask* m_task;
    u32 m_taskId;
    u8 m_priority;
    gfTask::Category m_category : 8;
    UnkTaskRequest(bool clear = true) {
        if (clear) {
            m_task = nullptr;
            m_taskId = 0;
            m_priority = 0;
            m_category = gfTask::Category_None;
        }
    }
};
static_assert(sizeof(UnkTaskRequest) == 0xC, "Class is the wrong size!");

class gfTaskScheduler {
    static const s32 unk14Size = 17;
    static const s32 unk58Size = 40;
    static const s32 unkF8Size = 14;

    s32 unk0_1 : 8;
    u32 unk0_2 : 8;
    bool unk2_b7 : 1;
    u32 unk2 : 15;
    u16 m_numRegisteredTasks;
    u16 unk6;
    gfTask* unk8;
    gfTask* unkC;
    gfTask* unk10;
    gfTask* unk14[unk14Size]; // grouped by priority?
    gfTask* unk58[unk58Size]; // grouped by Category
    gfTask* unkF8[unkF8Size]; // grouped by unk31
    gfTask* m_suspendList;
    u8 unk134[0xC];
    u16 m_numPendingPrioUpdates;
    UnkTaskRequest m_pendingPrioUpdates[0x4];
    u32 unk174;
public:
    static gfTaskScheduler* create();
    static gfTaskScheduler* getInstance();
    void clear();
    void updateStatusPre();
    void process(bool p1);
    void renderPre();
    void render();
    void updateStatus();
    void removeFromSuspendList(gfTask* task);
    void unlinkProcessList(gfTask* task);
    void unlink(gfTask* task);
    void link(gfTask* task);
    void registTask(gfTask* task);
    bool isRegist(const gfTask* task) const;
    gfTask* getTask(const char* name);
    gfTask* getTask(u32 id);
    gfTask* getTask(gfTask::Category ctgry, u32 pos);
    gfTask* getTaskById(gfTask::Category ctgry, u32 id);
    void setPauseCategory(gfTask::Category ctgry, bool isPaused);
    void changeTaskPriorityRequest(u32 id, u8 priority);

    gfTaskScheduler() :
      unk0_1(0),
      unk0_2(0),
      m_numRegisteredTasks(0),
      unk6(0),
      unk8(nullptr),
      unkC(nullptr),
      unk10(nullptr),
      m_suspendList(nullptr) {
        m_numPendingPrioUpdates = 0;
        clear();
    }

    void unregistTask(gfTask* task) {
        (void)task;
        m_numRegisteredTasks--;
    }

    s32 getUnk0_1() const { return unk0_1; }
    void setUnk2_7() { unk2_b7 = true; }
};
static_assert(sizeof(gfTaskScheduler) == 0x178, "Class is the wrong size!");

extern gfTaskScheduler* g_taskScheduler;
