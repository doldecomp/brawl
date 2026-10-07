#include <if/if_mngr.h>
#include <if/if_marth_final.h>
#include <mt/mt_vector.h>
#include <mt/mt_matrix.h>
#include <gf/gf_heap_manager.h>
#include <mu/mu_object.h>
#include <nw4r/g3d/g3d_scngroup.h>
#include <nw4r/g3d/g3d_obj.h>
#include <types.h>

// Stage-to-info projection; the last argument's purpose remains unknown.
extern "C" Vec3f fn_800DB360(const Vec3f* position, int unk1);
// Declaration-only call into the existing scene-group constructor.
extern "C" nw4r::g3d::ScnGroup* fn_801AB6CC(MEMAllocator* allocator, u32* size, u32 capacity);
void ScnMdl_SetNodeMtx(nw4r::g3d::ScnMdl*, u32, const Matrix*);

void ScnObj_EnableCallbackExecOp(nw4r::g3d::ScnObj*, u32);
void ScnObj_EnableCallbackTiming(nw4r::g3d::ScnObj*, u32);

// One resource entry describes the window model and its draw-priority offset.
struct MarthWindowModelData {
    const char* name;
    u8 first;
    u8 end;
    u8 priority;
    u8 unk7;
};
static const MarthWindowModelData windowModels[] = {{"InfWeapon0017_TopN", 0, 0, 128, 0}};
static MuAnimNameData windowAnimation = {0.0f, 60.0f, 0.0f, "InfWeapon0017_TopN__0", 8};

IfMarthFinalTask* IfMarthFinalTask::create(void* resourceData, HeapType heap, int priority) {
    IfMarthFinalTask* task = new (heap) IfMarthFinalTask(resourceData);
    nw4r::g3d::ResFile::Init(&task->m_resource);
    nw4r::g3d::ScnGroup* group = fn_801AB6CC(gfHeapManager::getMEMAllocator(heap), NULL, 1);
    task->initProc(&task->m_resource, group, priority, heap);
    return task;
}

void IfMarthFinalTask::initProc(nw4r::g3d::ResFile* resource, nw4r::g3d::ScnGroup* group, int priority, HeapType heap) {
    unk2C_b1 = false;
    initWork();
    createModel(resource, priority, heap);
    unk48 = reinterpret_cast<nw4r::g3d::ScnObj*>(group);
    nw4r::g3d::ScnObj* model = reinterpret_cast<nw4r::g3d::ScnObj*>(m_objects[0]->getSceneModel());
    group->Insert(group->sceneItemsCount, model);
    g_IfMngr->addGame2DObj(reinterpret_cast<nw4r::g3d::ScnObj*>(group));
    unk88 = 1;
}

void IfMarthFinalTask::createModel(nw4r::g3d::ResFile* resource, int priority, HeapType heap) {
    int i, j;
    const MarthWindowModelData* entry = windowModels;
    for (i = 0; i < 1; i++, entry++) {
        int count = entry->first < entry->end ? entry->end - entry->first : 1;
        for (j = 0; j < count; j++) {
            m_objects[entry->first + j] = MuObject::create(resource, entry->name, entry->priority + priority, NULL, heap);
            m_objects[entry->first + j]->m_modelAnim->setUpdateRate(0.0f);
        }
    }
    nw4r::g3d::ScnObj* scene = reinterpret_cast<nw4r::g3d::ScnObj*>(m_objects[0]->m_sceneModel);
    // BrawlHeaders lacks the scene callback member; its pointer is at 0xd4.
    *reinterpret_cast<void**>(reinterpret_cast<u8*>(scene) + 0xd4) = &m_callback;
    ScnObj_EnableCallbackExecOp(scene, 1);
    ScnObj_EnableCallbackTiming(scene, 1);
}

void IfMarthFinalTask::setAnim(int index) {
    m_objects[index]->setAnimName(&windowAnimation, false);
}

extern "C" {

void fn_106_D4E4(Vec3f* dst, const Vec3f* src);
void fn_106_DB68();
void fn_106_DB6C();
void fn_106_DB70();
void fn_106_DB74();

void fn_106_D4E4(Vec3f* dst, const Vec3f* src) {
    dst->m_x = src->m_x;
    dst->m_y = src->m_y;
    dst->m_z = src->m_z;
}

void fn_106_DB68() {}

void fn_106_DB6C() {}

void fn_106_DB70() {}

void fn_106_DB74() {}

}

#pragma dont_inline on
IfMarthFinalObjCallback::~IfMarthFinalObjCallback() {}

IfMarthFinalTask::~IfMarthFinalTask() {
    destroyModel();
    if (unk48 != NULL) reinterpret_cast<nw4r::g3d::G3dObj*>(unk48)->Destroy();
}
#pragma dont_inline off

void IfMarthFinalTask::processDefault() {}

// Convert the captured stage position once, after the scene computes world matrices.
void IfMarthFinalObjCallback::ExecCallback_CALC_WORLD(int timing, nw4r::g3d::ScnMdl* model) {
    if (timing == 1 && m_executed == 0) {
        Vec3f position;
        Vec3f rotation;
        Vec3f scale(1.0f, 1.0f, 1.0f);
        Vec3f converted = fn_800DB360(&m_position, 2);
        fn_106_D4E4(&position, &converted);
        // MATCH-ONLY: retain the zero temporary and the original load order.
        float zero = 0.0f;
        Matrix matrix;
        rotation.m_x = 0.0f;
        rotation.m_y = 0.0f;
        rotation.m_z = zero;
        matrix.setSRT(scale, rotation, position);
        ScnMdl_SetNodeMtx(model, 0, &matrix);
        m_executed = 1;
    }
}

void IfMarthFinalTask::dispOff(int) {
    if (unk88 == 1) {
        g_IfMngr->removeGame2DObj(unk48);
        unk88 = 0;
    }
}

u32 IfMarthFinalTask::isExecutedCallBack() const {
    return m_callback.m_executed;
}

void IfMngr::addGame2DObj(nw4r::g3d::ScnObj* object) {
    m_game2DGroup->Insert(m_game2DGroup->sceneItemsCount, object);
}

// MATCH-ONLY: preserve the shared out-of-line scene-removal helper.
#pragma dont_inline on
inline void IfMngr::removeGame2DObj(nw4r::g3d::ScnObj* object) {
    if (m_game2DGroup != NULL) m_game2DGroup->Remove(object);
}

#pragma dont_inline off

void IfMarthFinalTask::dispOn(int) {
    if (unk88 == 0) {
        g_IfMngr->addGame2DObj(unk48);
        unk88 = 1;
    }
}

void IfMarthFinalTask::setPos(Vec3f* position, int index) {
    m_objects[index]->setTrans(position);
}

Vec3f IfMarthFinalTask::getGlobalPos(int index) {
    return m_objects[index]->getGlobalPosition();
}

// Photo mode temporarily removes the whole window group from the game-2D scene.
void IfMarthFinalTask::setVisibilityWhole(bool visible) {
    if (visible == true && unk88 == 0) {
        g_IfMngr->addGame2DObj(unk48);
        unk88 = 1;
    } else if (visible == false && unk88 == 1) {
        g_IfMngr->removeGame2DObj(unk48);
        unk88 = 0;
    }
}

void IfMarthFinalTask::initWork() {
    unk48 = NULL;
    for (int i = 0; i < 1; i++) m_objects[i] = NULL;
    for (int i = 0; i < 1; i++) m_sceneObjects[i] = NULL;
}

void IfMarthFinalTask::destroyModel() {
    for (int i = 0; i < 1; i++) {
        if (m_sceneObjects[i] != NULL) {
            // BrawlHeaders omits ScnObj's G3dObj inheritance.
            reinterpret_cast<nw4r::g3d::G3dObj*>(m_sceneObjects[i])->Destroy();
            m_sceneObjects[i] = NULL;
        }
    }
    for (int i = 0; i < 1; i++) {
        if (m_objects[i] != NULL) {
            delete m_objects[i];
            m_objects[i] = NULL;
        }
    }
}

void IfMarthFinalTask::setPosConv(const Vec3f* position) {
    fn_106_D4E4(&m_callback.m_position, position);
}
