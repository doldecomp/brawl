#include <if/if_mngr.h>
#include <if/if_marth_final.h>
#include <mt/mt_vector.h>
#include <mu/mu_object.h>
#include <nw4r/g3d/g3d_scngroup.h>
#include <nw4r/g3d/g3d_obj.h>
#include <types.h>

extern "C" {

void fn_106_D4E4(Vec3f* dst, const Vec3f* src);
void fn_106_D9DC();
void fn_106_DB68();
void fn_106_DB6C();
void fn_106_DB70();
void fn_106_DB74();

void fn_106_D4E4(Vec3f* dst, const Vec3f* src) {
    dst->m_x = src->m_x;
    dst->m_y = src->m_y;
    dst->m_z = src->m_z;
}

void fn_106_D9DC() {}

void fn_106_DB68() {}

void fn_106_DB6C() {}

void fn_106_DB70() {}

void fn_106_DB74() {}

}

void IfMarthFinalTask::dispOff(int) {
    if (unk88 == 1) {
        g_IfMngr->removeGame2DObj(unk48);
        unk88 = 0;
    }
}

u32 IfMarthFinalTask::isExecutedCallBack() const {
    return unk84;
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
    fn_106_D4E4(&m_positionConv, position);
}
