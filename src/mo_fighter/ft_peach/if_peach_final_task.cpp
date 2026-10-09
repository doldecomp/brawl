#include <ft/peach/ft_peach.h>
#include <ft/ft_value_accesser.h>
#include <ft/ft_resource_id_accesser_impl.h>
#include <so/so_rot_utility.h>
#include <ft/peach/ft_peach_status_uniq_process_final.h>
#include <gf/gf_heap_manager.h>
#include <gf/gf_slow_manager.h>
#include <gf/gf_task_scheduler.h>
#include <gm/gm_global.h>
#include <if/if_mngr.h>
#include <it/it_manager.h>
#include <mt/mt_prng.h>
#include <mu/mu_object.h>
#include <nw4r/g3d/g3d_scngroup.h>
#include <nw4r/g3d/g3d_scnobj.h>
#include <nw4r/g3d/g3d_resfile.h>
#include <so/so_external_value_accesser.h>
#include <so/so_slow.h>
#include <so/so_module_accesser.h>
#include <st/stage.h>
#include <so/so_value_accesser.h>
#include <so/status/so_status_module_impl.h>
#include <snd/snd_system.h>
#include <types.h>

extern nw4r::g3d::ScnGroup* fn_801AB6CC(MEMAllocator*, u32*, u32);

struct PeachFinalModelData {
    const char* name;
    u8 firstIndex;
    u8 endIndex;
    u8 nodeIndex;
    u8 padding;
};

static const PeachFinalModelData s_peachFinalModelData[] = {
    { "InfWeapon0013_TopN", 0, 0, 0x80, 0 }
};

IfPeachFinalTask::IfPeachFinalTask(void* resourceData, u32 fighterTaskId)
    : gfTask("IfPeachFinal", Category_Info, 14, 6, true), m_resource(resourceData), unk44(-1),
      m_group(NULL), m_model(NULL), m_soundHandle(-1), m_fighterTaskId(fighterTaskId),
      m_actionActive(false), m_registered(false), unk5a() {}

IfPeachFinalTask* IfPeachFinalTask::create(void* resourceData, s32 heap, u32 fighterTaskId, bool initialize) {
    IfPeachFinalTask* task = new (Heaps::HeapType(heap)) IfPeachFinalTask(resourceData, fighterTaskId);
    nw4r::g3d::ResFile::Init(&task->m_resource);
    nw4r::g3d::ScnGroup* group = fn_801AB6CC(gfHeapManager::getMEMAllocator(Heaps::HeapType(heap)), NULL, 1);
    task->initProc(&task->m_resource, group, heap, initialize);
    return task;
}

void IfPeachFinalTask::initProc(nw4r::g3d::ResFile* resource, void* group, s32 heap, bool priorityOffset) {
    unk2C_b1 = false;
    initWork();
    createModel(resource, heap, priorityOffset);
    m_group = group;
    g_IfMngr->addGame2DObj(reinterpret_cast<nw4r::g3d::ScnObj*>(m_group));
    m_registered = true;
    nw4r::g3d::ScnObj* model = reinterpret_cast<nw4r::g3d::ScnObj*>(m_model->getSceneModel());
    reinterpret_cast<nw4r::g3d::ScnGroup*>(m_group)->Insert(reinterpret_cast<nw4r::g3d::ScnGroup*>(m_group)->sceneItemsCount, model);
    m_soundHandle = g_sndSystem->playSE(SndID(0x1B4A), -1, 0, 0, -1);
}

void IfPeachFinalTask::initWork() {
    m_group = NULL;
    for (int i = 0; i < 1; ++i) (&m_model)[i] = NULL;
}

void IfPeachFinalTask::createModel(nw4r::g3d::ResFile* resource, s32 heap, bool priorityOffset) {
    for (int dataIndex = 0; dataIndex < 1; ++dataIndex) {
        const PeachFinalModelData& data = s_peachFinalModelData[dataIndex];
        int modelCount = 1;
        if (data.firstIndex < data.endIndex) modelCount = data.endIndex - data.firstIndex;
        for (int modelIndex = 0; modelIndex < modelCount; ++modelIndex) {
            const int slot = data.firstIndex + modelIndex;
            MuObject* model = MuObject::create(resource, data.name,
                data.nodeIndex + (priorityOffset ? 1 : 0), NULL, Heaps::HeapType(heap));
            (&m_model)[slot] = model;
            model->m_modelAnim->setUpdateRate(0.0f);
        }
    }
}

void IfPeachFinalTask::destroyModel() {
    if (m_model != NULL) { delete m_model; m_model = NULL; }
}

void IfPeachFinalTask::setAction(int action) {
    static MuAnimNameData actions[4] = {
        {0.0f, 150.0f, 0.0f, "InfWeapon0013_TopN", 1},
        {0.0f, 60.0f, 0.0f, "InfWeapon0013_TopN_in", 1},
        {0.0f, 150.0f, 0.0f, "InfWeapon0013_TopN_out", 1},
        {0.0f, 60.0f, 0.0f, "InfWeapon0013_TopN_in_wide", 1}
    };
    m_model->setAnimName(&actions[action], true);
}

void IfPeachFinalTask::setRate(float rate) {
    for (int i = 0; i < 1; ++i) {
        MuObject* model = (&m_model)[i];
        if (model != NULL) model->m_modelAnim->setUpdateRate(rate);
    }
}

void IfPeachFinalTask::setVisibilityWhole(bool visible) {
    if (visible && !m_registered) {
        g_IfMngr->addGame2DObj(reinterpret_cast<nw4r::g3d::ScnObj*>(m_group));
        m_registered = true;
    } else if (!visible && m_registered) {
        if (g_IfMngr->m_game2DGroup != NULL) {
            g_IfMngr->removeGame2DObj(reinterpret_cast<nw4r::g3d::ScnObj*>(m_group));
        }
        m_registered = false;
    }
}

void IfPeachFinalTask::processFixPosition() {
    // HYPOTHESIS: native reads the global slow-rate multiplier from soSlow +0x44.
    float rate = *reinterpret_cast<float*>(reinterpret_cast<u8*>(soSlow::getInstance()) + 0x44);
    rate *= gfSlowManager::getQuickRate();
    float fighterSlowRate = 1.0f;
    gfTask* fighterTask = gfTaskScheduler::getInstance()->getTaskById(gfTask::Category_Fighter, m_fighterTaskId);
    ftPeach* peach = dynamic_cast<ftPeach*>(fighterTask);
    if (peach != NULL) fighterSlowRate = soExternalValueAccesser::getSlowRate(peach);
    rate *= fighterSlowRate;
    setRate(rate);
    if (soSlow::getInstance()->isAdjust() == true && m_actionActive == true && m_model->isNodeAnimFinished() == true) {
        gfTask* fighter = gfTaskScheduler::getInstance()->getTaskById(gfTask::Category_Fighter, m_fighterTaskId);
        ftPeach* finalFighter = dynamic_cast<ftPeach*>(fighter);
        if (finalFighter != NULL) finalFighter->endFinalRequest();
        exit();
    }
}

IfPeachFinalTask::~IfPeachFinalTask() {
    if (m_soundHandle >= 0) {
        g_sndSystem->stopSE(m_soundHandle, 0);
        m_soundHandle = -1;
    }
    destroyModel();
    if (m_group != NULL) reinterpret_cast<nw4r::g3d::G3dObj*>(m_group)->Destroy();
    gfTask* fighter = gfTaskScheduler::getInstance()->getTaskById(gfTask::Category_Fighter, m_fighterTaskId);
    ftPeach* peach = dynamic_cast<ftPeach*>(fighter);
    if (peach != NULL) peach->endFinalRequest();
}
