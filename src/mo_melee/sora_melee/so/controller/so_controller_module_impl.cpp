#include <cmath>
#include <so/controller/so_controller_module_impl.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <types.h>

soControllerModuleImpl::soControllerModuleImpl(s16 manageID, int unk, soArray<soControllerClatter>* clatters)
    : soAnimCmdEventObserver(5, manageID), m_clatters(clatters) { }

soControllerModuleImpl::~soControllerModuleImpl() { }

void soControllerModuleImpl::activate() {
    int size = m_clatters->size();
    for (int i = 0; i < size; i++) {
        m_clatters->at(i).reset();
    }
}

void soControllerModuleImpl::deactivate() { }

void soControllerModuleImpl::updateClatter(soController* linkController) {
    soControllerClatter* clatter;
    int size = m_clatters->size();
    for (int i = 0; i < size; i++) {
        if (m_clatters->at(i).m_time > 0.0f) {
            clatter = &m_clatters->at(i);
            clatter->update(linkController, soControllerClatter::checkButton(linkController), getClatterThreshold(i));
        }
    }
}

void soControllerModuleImpl::startClatter(float time, float p2, float p3, u8 p4, u8 p5, u32 index, bool p7) {
    if (p7 == true || (s8) p5 == -1 || (s8) m_clatters->at(index).m_unk10 != (s8) p5) {
        m_clatters->at(index).m_time = time;
    } else {
        m_clatters->at(index).m_time += time;
    }
    m_clatters->at(index).m_unk04 = p2;
    m_clatters->at(index).m_unk08 = p3;
    soControllerClatter& first = m_clatters->at(index);
    soControllerClatter& second = m_clatters->at(index);
    first.m_unk0D = 0;
    second.m_unk0D = 0;
    m_clatters->at(index).m_unk0F = p4;
    m_clatters->at(index).m_unk0E = 0;
    m_clatters->at(index).m_unk10 = p5;
}

void soControllerModuleImpl::setClatterTime(float time, u32 index) {
    m_clatters->at(index).m_time = time;
    if (m_clatters->at(index).m_time < 0.0f) {
        float& t = m_clatters->at(index).m_time;
        t = 0.0f;
    }
}

void soControllerModuleImpl::addClatterTime(float time, u32 index) {
    m_clatters->at(index).m_time += time;
    if (m_clatters->at(index).m_time < 0.0f) {
        float& t = m_clatters->at(index).m_time;
        t = 0.0f;
    }
}

float soControllerModuleImpl::getClatterTime(u32 index) {
    return m_clatters->at(index).m_time;
}

void soControllerModuleImpl::endClatter(u32 index) {
    float& t = m_clatters->at(index).m_time;
    t = 0.0f;
}

bool soControllerModuleImpl::notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* moduleAccesser, s32 unk3) {
    return false;
}

bool soControllerModuleImpl::isObserv(char unk1) {
    return unk1 == 7;
}

void soControllerModuleImpl::setRumble(s32, s32, bool, s32) { }
void soControllerModuleImpl::setRumbleAll(s32, s32, s32) { }
void soControllerModuleImpl::stopRumbleKind(s32, s32) { }
void soControllerModuleImpl::stopRumbleAll(s32, s32) { }
void soControllerModuleImpl::resetFlickBonusLr() { }
void soControllerModuleImpl::resetFlickBonus() { }
u8 soControllerModuleImpl::getFlickBonusLr() { return 0; }
u8 soControllerModuleImpl::getFlickBonus() { return 0; }
float soControllerModuleImpl::getLr() { return 0.0f; }
void soControllerModuleImpl::setReverseXFrame(s32, bool) { }
void soControllerModuleImpl::stopRumble(bool) { }

bool soControllerModuleImpl::isSubStickSide() {
    float dir = fabs(getSubStickDir());
    return dir < 0.87266463f;
}

float soControllerModuleImpl::getSubStickDir() {
    return atan2(getSubStickY(), (float) fabs(getSubStickX()));
}

bool soControllerModuleImpl::isStickSide() {
    float dir = fabs(getStickDir());
    return dir < 0.87266463f;
}

float soControllerModuleImpl::getStickDir() {
    return atan2(getStickY(), (float) fabs(getStickX()));
}

float soControllerModuleImpl::getStickAngle() {
    return atan2(getStickY(), getStickX());
}
