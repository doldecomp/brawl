#include <st_fzero/gr_fzero.h>
#include <gr/gr_calc_world_callback.h>
#include <math.h>
#include <nw4r/math/math_arithmetic.h>
#include <nw4r/math/math_triangular.h>

grFzeroAttack::grFzeroAttack(const char* taskName) : grFzero(taskName) {
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
        case 4:
        case 5:
            updateYakumonoFloor(deltaFrame);
            break;
        case 6:
            updateYakumonoWall(deltaFrame);
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

    Vec3f a(mtx[22].m[0][3], mtx[22].m[1][3], 0.0f);
    Vec3f b(mtx[23].m[0][3], mtx[23].m[1][3], 0.0f);
    Vec3f d;
    d = b - a;

    bool tooShort = false;
    if (fzeroIsNearZero(d.m_x) && fzeroIsNearZero(d.m_y) && fzeroIsNearZero(d.m_z)) {
        tooShort = true;
    }
    if (!tooShort) {
        Vec3f p;
        switch (*m_sceneWork) {
        case 5:
        case 6:
            if (a.m_y < b.m_y) {
                p = a;
            } else if (a.m_y > b.m_y) {
                p = b;
            } else {
                p = a;
            }
            m_pos.m_y = p.m_y - 25.0f;
            break;
        default: {
            float length = d.m_z * d.m_z + (d.m_x * d.m_x + d.m_y * d.m_y);
            if ((float)fabs(length) <= 1.17549435e-38f) {
                length = 0.0f;
            } else {
                length = length * rsqrtf(length);
            }
            d.normalize();
            float half = 0.5f * length;
            d.m_x = d.m_x * half;
            d.m_y = d.m_y * half;
            d.m_z = d.m_z * half;
            p = a + d;
            m_pos.m_y = p.m_y - 25.0f;
        }
        }
        Vec3f offset(0.0f, 0.0f, 0.0f);
        if (m_type == 4) {
            offset.m_x = __fabsf(a.m_x);
            offset.m_y = 0.0f;
            offset.m_z = 0.0f;
        }
        if (m_type == 5) {
            offset.m_x = __fabsf(b.m_x);
            offset.m_y = 0.0f;
            offset.m_z = 0.0f;
        }
        setOffsetAttack(&offset, 0);
    }

    int index = 0xff;
    Vec3f origin(m_pos.m_x, m_pos.m_y + 25.0f, m_pos.m_z);
    float tilt;
    switch (*m_sceneWork) {
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
    switch (*m_sceneWork) {
    case 5:
    case 6:
        if (a.m_y < b.m_y) {
            index = 0;
            target = a;
        } else if (a.m_y > b.m_y) {
            index = 1;
            target = b;
        } else {
            index = 0;
            target = a;
        }
        break;
    default:
        if (m_type == 4) {
            target = a;
        } else if (m_type == 5) {
            target = b;
        }
    }

    tooShort = false;
    d = target - origin;
    if (fzeroIsNearZero(d.m_x) && fzeroIsNearZero(d.m_y) && fzeroIsNearZero(d.m_z)) {
        tooShort = true;
    }
    if (!tooShort) {
        d.normalize();
        m_rot.m_x = 0.0f;
        m_rot.m_y = 0.0f;
        float angle = nw4r::math::Atan2Deg(d.m_y, d.m_x);
        m_rot.m_z = angle;
        if (index == 0 && m_type == 5) {
            if (angle <= 0.0f) {
                m_rot.m_z = angle + 180.0f;
            } else if (angle >= 0.0f) {
                m_rot.m_z = angle - 180.0f;
            }
        }
        if (index == 1 && m_type == 4) {
            angle = m_rot.m_z;
            if (angle <= 0.0f) {
                m_rot.m_z = angle + 180.0f;
            } else if (angle >= 0.0f) {
                m_rot.m_z = angle + 180.0f;
            }
        }
        if (m_type == 4) {
            angle = m_rot.m_z;
            if (angle >= 0.0f) {
                m_rot.m_z = fzeroClamp(angle, 180.0f - tilt, 180.0f);
            } else if (angle <= 0.0f) {
                m_rot.m_z = fzeroClamp(angle, -180.0f, -(180.0f - tilt));
            }
        } else if (m_type == 5) {
            angle = m_rot.m_z;
            if (angle >= 0.0f) {
                m_rot.m_z = fzeroClamp(angle, 0.0f, tilt);
            } else if (angle <= 0.0f) {
                m_rot.m_z = fzeroClamp(angle, -tilt, 0.0f);
            }
        }
    }

    switch (*m_stateWork) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        if (m_attackEnabled == 1) {
            disableAttack(0);
            m_attackEnabled = 0;
        }
        break;
    default:
        if (25.0f + m_pos.m_y < m_posLimitWork[4]) {
            if (m_attackEnabled == 1) {
                disableAttack(0);
                m_attackEnabled = 0;
            }
        } else if (m_attackEnabled == 0) {
            setAttack();
        }
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
            m_pos = m_mtxGimmickWork[39].getPosition();
            m_state = 3;
        }
        break;
    case 3:
        m_pos = mtx[39].getPosition();
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
            calcWorldCallBack->m_nodeCallbackDatas[0].m_pos = m_pos;
            calcWorldCallBack->m_nodeCallbackDatas[0].m_rot = m_rot;
        }
    }
}

void grFzeroAttack::setAttack() {
    switch (m_type) {
    case 4:
    case 5:
        setAttackFloor();
        break;
    case 6:
        setAttackWall();
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
