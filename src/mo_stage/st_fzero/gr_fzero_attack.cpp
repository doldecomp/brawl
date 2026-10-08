#include <st_fzero/gr_fzero.h>
#include <gr/gr_calc_world_callback.h>
#include <math.h>
#include <nw4r/math/math_arithmetic.h>
#include <nw4r/math/math_triangular.h>

inline grFzeroAttack::grFzeroAttack(const char* taskName) : grFzero(taskName) {
    m_stateWork = NULL;
    m_stateWallWork = NULL;
    m_sceneWork = NULL;
    m_frameSceneWork = NULL;
    m_mtxGimmickWork = NULL;
    m_posLimitWork = NULL;
    m_pos.m_x = 0.0f;
    m_pos.m_y = 0.0f;
    m_pos.m_z = 0.0f;
    m_rot.m_x = 0.0f;
    m_rot.m_y = 0.0f;
    m_rot.m_z = 0.0f;
    m_type = 7;
    m_hasYakumono = 0;
    m_attackEnabled = 0;
    m_work = NULL;
    grCalcWorldCallBack* callback = &m_calcWorldCallBack;
    if (callback == NULL) {
        return;
    }
    callback->m_numNodeCallbackData = 1;
    callback->initialize(false, Heaps::StageInstance);
    callback->m_nodeCallbackDatas[0].m_flags |= 1;
    callback->m_nodeCallbackDatas[0].m_flags |= 2;
}

grFzeroAttack* grFzeroAttack::create(int mdlIndex, const char* nodeName, const char* taskName) {
    grFzeroAttack* ground = new (Heaps::StageInstance) grFzeroAttack(taskName);
    if (ground != NULL) {
        ground->setMdlIndex(mdlIndex);
        ground->setTgtNode(nodeName);
    }
    return ground;
}

grFzeroAttack::~grFzeroAttack() {
    if (m_work != NULL) {
        delete m_work;
    }
    m_work = NULL;
}

void grFzeroAttack::update(float deltaFrame) {
    grGimmick::update(deltaFrame);
    if (m_isUpdate) {
        updateYakumono(deltaFrame);
        updateCallBack(deltaFrame);
    }
}

// Creates the hit (setHit) once the object is there, then keeps its area on the floor or wall it belongs to.
void grFzeroAttack::updateYakumono(float deltaFrame) {
    if (m_hasYakumono == 1) {
        switch (m_type) {
        case 6:
            updateYakumonoWall(deltaFrame);
            break;
        case 4:
        case 5:
            updateYakumonoFloor(deltaFrame);
            break;
        }
    } else {
        setHit();
        if (m_yakumono != NULL) {
            m_hasYakumono = 1;
        }
    }
}

// HYPOTHESIS: the same fsel based clamp helper the glide statuses use.
static inline float fzeroClamp(float value, float lo, float hi) {
    value = nw4r::math::FSelect(value - lo, value, lo);
    return nw4r::math::FSelect(value - hi, hi, value);
}

// The hit area of the two floors: it sits below the middle of the course edge segment (between the stage's two
// courseCol nodes) and is tilted to follow it, within limits that depend on the course section.
void grFzeroAttack::updateYakumonoFloor(float deltaFrame) {
    Matrix* mtx = m_mtxGimmickWork;
    if (mtx == NULL) {
        return;
    }

    Vec3f a;
    Vec3f b;
    a.m_x = mtx[22].m[0][3];
    a.m_y = mtx[22].m[1][3];
    b.m_x = mtx[23].m[0][3];
    b.m_y = mtx[23].m[1][3];
    a.m_z = 0.0f;
    b.m_z = 0.0f;
    Vec3f d;
    d.m_z = 0.0f;
    d.m_x = b.m_x - a.m_x;
    d.m_y = b.m_y - a.m_y;

    bool tooShort = false;
    if (fabs(d.m_x) < 1e-5f && fabs(d.m_y) < 1e-5f) {
        tooShort = true;
    }
    if (!tooShort) {
        Vec3f p;
        if (*m_sceneWork < 7 && *m_sceneWork > 4) {
            p.m_x = a.m_x;
            p.m_y = a.m_y;
            if (b.m_y <= a.m_y && b.m_y < a.m_y) {
                p.m_x = b.m_x;
                p.m_y = b.m_y;
            }
            p.m_z = 0.0f;
            m_pos.m_y = p.m_y - 25.0f;
        } else {
            float length = d.m_x * d.m_x + d.m_y * d.m_y + d.m_z * d.m_z;
            if ((float)fabs(length) > 1.17549435e-38f) {
                length = length * rsqrtf(length);
            } else {
                length = 0.0f;
            }
            d.normalize();
            float half = length * 0.5f;
            d.m_x = d.m_x * half;
            d.m_y = d.m_y * half;
            d.m_z = d.m_z * half;
            p.m_x = a.m_x + d.m_x;
            p.m_y = a.m_y + d.m_y;
            p.m_z = a.m_z + d.m_z;
            m_pos.m_y = p.m_y - 25.0f;
        }
        Vec3f offset;
        offset.m_x = 0.0f;
        if (m_type == 4) {
            offset.m_x = fabs(a.m_x);
        }
        if (m_type == 5) {
            offset.m_x = fabs(b.m_x);
        }
        offset.m_z = 0.0f;
        offset.m_y = 0.0f;
        setOffsetAttack(&offset, 0);
    }

    int index = 0xff;
    Vec3f origin;
    origin.m_x = m_pos.m_x;
    origin.m_y = m_pos.m_y + 25.0f;
    origin.m_z = m_pos.m_z;
    u8 scene = *m_sceneWork;
    float tilt;
    switch (scene) {
    case 0:
        tilt = 10.0f;
        break;
    case 1:
        tilt = 10.0f;
        break;
    case 2:
        tilt = 0.0f;
        break;
    case 3:
        tilt = 0.0f;
        break;
    case 4:
        tilt = 0.0f;
        break;
    case 5:
        tilt = 0.0f;
        break;
    case 6:
        tilt = 0.0f;
        break;
    default:
        tilt = 0.0f;
    }

    Vec3f target;
    if (scene < 7 && scene > 4) {
        if (b.m_y <= a.m_y) {
            if (a.m_y <= b.m_y) {
                index = 0;
                target = a;
            } else {
                index = 1;
                target = b;
            }
        } else {
            index = 0;
            target = a;
        }
    } else if (m_type == 4) {
        target = a;
    } else if (m_type == 5) {
        target = b;
    }

    tooShort = false;
    d.m_x = target.m_x - origin.m_x;
    d.m_y = target.m_y - origin.m_y;
    d.m_z = target.m_z - origin.m_z;
    if (fabs(d.m_x) < 1e-5f && fabs(d.m_y) < 1e-5f && fabs(d.m_z) < 1e-5f) {
        tooShort = true;
    }
    if (!tooShort) {
        d.normalize();
        m_rot.m_x = 0.0f;
        m_rot.m_y = 0.0f;
        float angle = nw4r::math::Atan2Deg(d.m_y, d.m_x);
        m_rot.m_z = angle;
        if (index == 0 && m_type == 5) {
            if (angle > 0.0f) {
                m_rot.m_z = angle - 180.0f;
            } else {
                m_rot.m_z = angle + 180.0f;
            }
        }
        if (index == 1 && m_type == 4) {
            angle = m_rot.m_z;
            if (angle > 0.0f) {
                m_rot.m_z = angle + 180.0f;
            } else {
                m_rot.m_z = angle + 180.0f;
            }
        }
        if (m_type == 4) {
            angle = m_rot.m_z;
            if (angle < 0.0f) {
                m_rot.m_z = fzeroClamp(angle, -180.0f, -(180.0f - tilt));
            } else {
                m_rot.m_z = fzeroClamp(angle, 180.0f - tilt, 180.0f);
            }
        } else if (m_type == 5) {
            angle = m_rot.m_z;
            if (angle < 0.0f) {
                m_rot.m_z = fzeroClamp(angle, -tilt, 0.0f);
            } else {
                m_rot.m_z = fzeroClamp(angle, 0.0f, tilt);
            }
        }
    }

    if (*m_stateWork < 6 && *m_stateWork != 0) {
        if (m_attackEnabled == 1) {
            disableAttack(0);
            m_attackEnabled = 0;
        }
    } else if (m_posLimitWork[4] <= m_pos.m_y + 25.0f) {
        if (m_attackEnabled == 0) {
            setAttack();
        }
    } else if (m_attackEnabled == 1) {
        disableAttack(0);
        m_attackEnabled = 0;
    }
}

// The hit area of the wall follows the stage's "wall_col_move" matrix while the wall is there.
void grFzeroAttack::updateYakumonoWall(float deltaFrame) {
    Matrix* mtx = m_mtxGimmickWork;
    if (mtx == NULL) {
        return;
    }
    switch (m_state) {
    case 2:
        break;
    case 0:
        m_state = 1;
        // fall through
    case 1:
        if (*m_stateWallWork == 7) {
            setAttack();
            mtx = m_mtxGimmickWork;
            m_pos.m_x = mtx[39].m[0][3];
            m_pos.m_y = mtx[39].m[1][3];
            m_pos.m_z = mtx[39].m[2][3];
            m_state = 3;
        }
        break;
    case 3:
        m_pos.m_x = mtx[39].m[0][3];
        m_pos.m_y = mtx[39].m[1][3];
        m_pos.m_z = mtx[39].m[2][3];
        if (*m_stateWallWork != 7) {
            if (m_attackEnabled == 1) {
                disableAttack(0);
                m_attackEnabled = 0;
            }
            m_state = 1;
        }
        break;
    }
}

// The hit area follows m_pos / m_rot.
void grFzeroAttack::updateCallBack(float deltaFrame) {
    grCalcWorldCallBack* calcWorldCallBack = &m_calcWorldCallBack;
    if (calcWorldCallBack != NULL) {
        nw4r::g3d::ScnMdl* scnMdl = m_sceneModels[0];
        if (scnMdl != NULL) {
            if (scnMdl->m_calcWorldCallBack == NULL) {
                calcWorldCallBack->m_index = 0;
                calcWorldCallBack->m_nodeCallbackDatas[0].m_nodeIndex = m_nodeIndex;
                scnMdl->m_calcWorldCallBack = calcWorldCallBack;
                scnMdl->EnableScnMdlCallbackTiming(1);
                scnMdl->m_nodeIndex = calcWorldCallBack->m_nodeCallbackDatas[0].m_nodeIndex;
            }
            calcWorldCallBack->m_nodeCallbackDatas[0].m_pos.m_x = m_pos.m_x;
            calcWorldCallBack->m_nodeCallbackDatas[0].m_pos.m_y = m_pos.m_y;
            calcWorldCallBack->m_nodeCallbackDatas[0].m_pos.m_z = m_pos.m_z;
            calcWorldCallBack->m_nodeCallbackDatas[0].m_rot.m_x = m_rot.m_x;
            calcWorldCallBack->m_nodeCallbackDatas[0].m_rot.m_y = m_rot.m_y;
            calcWorldCallBack->m_nodeCallbackDatas[0].m_rot.m_z = m_rot.m_z;
        }
    }
}

void grFzeroAttack::setAttack() {
    switch (m_type) {
    case 6:
        setAttackWall();
        break;
    case 4:
    case 5:
        setAttackFloor();
        break;
    }
}

// A hit box of 30 units above the floor line (size 30, power 15, knocked up at 90 degrees), enabled once.
void grFzeroAttack::setAttackFloor() {
    if (m_attackEnabled == 1) {
        return;
    }

    soCollisionAttackData attack(1.0f);
    Vec3f offset;
    offset.m_x = 10.0f;
    offset.m_y = 0.0f;
    offset.m_z = 0.0f;
    float one = 1.0f;

    setAttackGimmickDetails(&attack, 30.0f, one, one, one,
        15, &offset, 90, 50, 100, 80, 0,
        0x3FF, 7, false, 15,
        soCollisionAttackData::Attribute_Normal, soCollisionAttackData::Sound_Level_Large,
        soCollisionAttackData::Sound_Attribute_Kick,
        false, false, false, false, false, false, 0, 60,
        false, false, false, soCollisionAttackData::Lr_Check_Pos,
        false, false, false, false, false, soCollisionAttackData::Region_None, true);
    m_yakumono->setAttack(0, 0, &attack);
    m_attackEnabled = 1;
}

// The wall hits sideways (power 10, no knockback angle) and always faces right.
void grFzeroAttack::setAttackWall() {
    if (m_attackEnabled == 1) {
        return;
    }

    soCollisionAttackData attack(1.0f);
    Vec3f offset;
    offset.m_x = 0.0f;
    offset.m_y = -100.0f;
    offset.m_z = 0.0f;
    float one = 1.0f;

    setAttackGimmickDetails(&attack, 5.0f, one, one, one,
        10, &offset, 0, 100, 0, 80, 0,
        0x3FF, 7, false, 15,
        soCollisionAttackData::Attribute_Normal, soCollisionAttackData::Sound_Level_Large,
        soCollisionAttackData::Sound_Attribute_Kick,
        false, false, false, false, false, false, 0, 60,
        false, false, false, soCollisionAttackData::Lr_Check_Forward,
        false, false, false, false, false, soCollisionAttackData::Region_None, true);
    m_yakumono->setLr(one);
    m_yakumono->setAttack(0, 0, &attack);
    m_attackEnabled = 1;
}
