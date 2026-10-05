#include <cmath>
#include <so/controller/so_controller_module_impl.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <types.h>

// HYPOTHESIS: a table (not folded into the float pool) holding the 50 degrees (in radians) "side" angle limit.
static const float s_sideAngle[] = { 0.87266463f };

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

typedef soArrayContractibleTable<const acCmdArgConv> ArgTable;

// MATCH-ONLY helpers mirroring the inlined argument accessors.
static inline acCmdArg getFrontArg(const ArgTable& args) {
    return acCmdArg(&args.at(0));
}

static inline void shiftArg(ArgTable& args) {
    args.shift();
}

// MATCH-ONLY: macro so the "unsupported argument type" early return stays a direct branch.
#define READ_FLOAT_ARG(args, accesser, out)                                                            if (getFrontArg(args).getArgType() == 1) {                                                             out = getFrontArg(args).getFloatData();                                                        } else if (getFrontArg(args).getArgType() == 5) {                                                      out = (float) soValueAccesser::getValueInt(accesser, getFrontArg(args).getIntData(), 0);       } else {                                                                                               return true;                                                                                   }

bool soControllerModuleImpl::notifyEventAnimCmd(acAnimCmd* cmd, soModuleAccesser* accesser, s32 unk3) {
    s32 group = cmd->getGroup();
    if (!isObserv(group)) {
        return false;
    }
    if (cmd->getType() <= -1 || cmd->getType() >= 13) {
        return false;
    }
    switch (cmd->getType()) {
    case 0:
        resetFlickX();
        return true;
    case 1:
        resetFlickY();
        return true;
    case 2:
        resetTrigger();
        return true;
    case 3: {
        s32 argNum = cmd->getArgNum();
        if (argNum < 3) {
            return true;
        }
        ArgTable args = cmd->getArgList();
        float time, p2, p3;
        READ_FLOAT_ARG(args, accesser, time)
        shiftArg(args);
        READ_FLOAT_ARG(args, accesser, p2)
        shiftArg(args);
        READ_FLOAT_ARG(args, accesser, p3)
        shiftArg(args);
        bool flag = false;
        if (argNum > 3) {
            flag = getFrontArg(args).getBoolData();
            shiftArg(args);
        }
        s32 kind = -1;
        if (argNum > 4) {
            kind = getFrontArg(args).getIntData();
            shiftArg(args);
        }
        u32 index = 0;
        if (argNum > 5) {
            index = getFrontArg(args).getIntData();
            shiftArg(args);
        }
        startClatter(time, p2, p3, flag, (char) kind, index, false);
        return true;
    }
    case 4:
    case 5: {
        if (cmd->getArgNum() < 1) {
            return true;
        }
        ArgTable args = cmd->getArgList();
        float time;
        READ_FLOAT_ARG(args, accesser, time)
        shiftArg(args);
        u32 index = 0;
        if (cmd->getArgNum() > 1) {
            index = getFrontArg(args).getIntData();
        }
        if (cmd->getType() == 5) {
            time *= -1.0f;
        }
        addClatterTime(time, index);
        return true;
    }
    case 6: {
        if (cmd->getArgNum() < 1) {
            return true;
        }
        acCmdArg arg;
        cmd->getArg(&arg, 0);
        return true;
    }
    case 7:
    case 9:
    case 11: {
        acCmdArg arg;
        if (!cmd->getArg(&arg, 0)) {
            return true;
        }
        s32 a = arg.getIntData();
        s32 b = 0;
        if (cmd->getArg(&arg, 1) == true) {
            b = arg.getIntData();
        }
        switch (cmd->getType()) {
        case 7:
            setRumble(a, b, false, -1);
            break;
        case 11:
            setRumble(a, b, true, -1);
            break;
        case 9:
            setRumbleAll(a, b, -1);
            break;
        }
        return true;
    }
    case 8:
    case 10: {
        if (cmd->getArgNum() != 1) {
            return true;
        }
        ArgTable args = cmd->getArgList();
        const acCmdArg& arg = getFrontArg(args);
        if (arg.getArgType() != 0) {
            return true;
        }
        if (cmd->getType() == 8) {
            stopRumbleKind(arg.getIntData(), -1);
        } else {
            stopRumbleAll(arg.getIntData(), -1);
        }
        return true;
    }
    default:
        return false;
    }
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
    return dir < s_sideAngle[0];
}

float soControllerModuleImpl::getSubStickDir() {
    return atan2(getSubStickY(), (float) fabs(getSubStickX()));
}

bool soControllerModuleImpl::isStickSide() {
    float dir = fabs(getStickDir());
    return dir < s_sideAngle[0];
}

float soControllerModuleImpl::getStickDir() {
    return atan2(getStickY(), (float) fabs(getStickX()));
}

float soControllerModuleImpl::getStickAngle() {
    return atan2(getStickY(), getStickX());
}
