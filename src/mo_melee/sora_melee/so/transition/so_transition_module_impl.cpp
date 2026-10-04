#include <so/transition/so_transition_module_impl.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <types.h>

int soTransitionModuleImpl::checkEstablish(soModuleAccesser* accesser, u32* targetKindOut, int groupID, u16* attrMask, soGeneralTermCache* generalTermCache) {
    if (groupID != -1) {
        soTransitionTermGroup& group = m_transitionTermGroupArray->at(groupID);
        if (!group.m_enable.isEnable()) {
            return 0;
        }
        int termID = -1;
        u32 returnWord = 0;
        if (group.checkEstablish(accesser, targetKindOut, &termID, &returnWord, attrMask, generalTermCache) == 1) {
            soTransitionInfo info;
            info.m_groupId = groupID;
            info.m_unitId = termID;
            info._unk08 = returnWord;
            m_transitionInfo = info;
            return 1;
        }
        return 0;
    }
    int size = m_transitionTermGroupArray->size();
    for (int i = 0; i < size; i++) {
        soTransitionTermGroup& group = m_transitionTermGroupArray->at(i);
        if (group.m_enable.isEnable()) {
            int termID = -1;
            u32 returnWord = 0;
            if (group.checkEstablish(accesser, targetKindOut, &termID, &returnWord, attrMask, generalTermCache) == 1) {
                soTransitionInfo info;
                info.m_groupId = i;
                info.m_unitId = termID;
                info._unk08 = returnWord;
                m_transitionInfo = info;
                return 1;
            }
        }
    }
    return 0;
}

void soTransitionModuleImpl::clearTransitionTermAll(int groupID) {
    if (groupID != -1) {
        m_transitionTermGroupArray->at(groupID).clearTransitionTermAll();
    } else {
        for (int i = 0; i < m_transitionTermGroupArray->size(); i++) {
            m_transitionTermGroupArray->at(i).clearTransitionTermAll();
        }
    }
}

int soTransitionModuleImpl::addTerm(int groupID, soTransitionTerm* term, int unitID, u32 targetKind, u16* option) {
    if (m_transitionTermGroupArray->at(groupID <= -1 ? m_groupID : groupID).isFull() == 1) {
        return -1;
    }
    return m_transitionTermGroupArray->at(groupID <= -1 ? m_groupID : groupID).addTerm(unitID, targetKind, term, option);
}

void soTransitionModuleImpl::addGeneralTerm(int groupID, int unitID, soGeneralTerm* term) {
    m_transitionTermGroupArray->at(groupID <= -1 ? m_groupID : groupID).addGeneralTerm(unitID, *term);
}

void soTransitionModuleImpl::addGeneralTermLastTerm(int groupID, soGeneralTerm* term) {
    m_transitionTermGroupArray->at(groupID <= -1 ? m_groupID : groupID).addGeneralTermLastTerm(*term);
}

void soTransitionModuleImpl::enableTerm(int unitID, int groupID) {
    m_transitionTermGroupArray->at(groupID <= -1 ? m_groupID : groupID).enableTerm(unitID);
}

void soTransitionModuleImpl::unableTerm(int unitID, int groupID) {
    m_transitionTermGroupArray->at(groupID <= -1 ? m_groupID : groupID).unableTerm(unitID);
}

void soTransitionModuleImpl::enableTermAll(int groupID) {
    m_transitionTermGroupArray->at(groupID <= -1 ? m_groupID : groupID).enableTermAll();
}

void soTransitionModuleImpl::unableTermAll(int groupID) {
    m_transitionTermGroupArray->at(groupID <= -1 ? m_groupID : groupID).unableTermAll();
}

void soTransitionModuleImpl::enableTermGroup(int groupID) {
    m_transitionTermGroupArray->at(groupID <= -1 ? m_groupID : groupID).m_enable.enable();
}

void soTransitionModuleImpl::unableTermGroup(int groupID) {
    m_transitionTermGroupArray->at(groupID <= -1 ? m_groupID : groupID).m_enable.disable();
}

bool soTransitionModuleImpl::isEnableTermGroup(int groupID) {
    return m_transitionTermGroupArray->at(groupID <= -1 ? m_groupID : groupID).m_enable.isEnable();
}

static inline s32 readIntArg(soArrayContractibleTable<acCmdArgConv>& args) {
    acCmdArg arg;
    arg.setDataPtr(&args.at(0));
    arg.setNull(false);
    s32 v = arg.getIntData();
    args.shift();
    return v;
}

int soTransitionModuleImpl::notifyEventAnimCmd(int commandType, soArrayContractibleTable<acCmdArgConv> commandArgList, u8* option, soModuleAccesser* accesser) {
    if (commandType <= -1 || commandType >= 14) {
        return 0;
    }
    soArrayContractibleTable<acCmdArgConv> args(commandArgList);
    switch (commandType) {
    case 4:
        addGeneralTermLastTerm(-1, (soGeneralTerm*) &args);
        return 1;
    case 5: {
        s32 group = readIntArg(args);
        s32 unit = readIntArg(args);
        addGeneralTerm(group, unit, (soGeneralTerm*) &args);
        return 1;
    }
    default:
        return 0;
    }
}

soTransitionInfo* soTransitionModuleImpl::getLastTransitionInfo() {
    return &m_transitionInfo;
}

soTransitionModuleImpl::~soTransitionModuleImpl() { }
