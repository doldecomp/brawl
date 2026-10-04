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

// MATCH-ONLY: first remaining argument of the (consumed-as-read) argument list.
static inline acCmdArg getFrontArg(const soArrayContractibleTable<acCmdArgConv>& args) {
    return acCmdArg(&args.at(0));
}

static inline void shiftArg(soArrayContractibleTable<acCmdArgConv>& args) {
    args.shift();
}

int soTransitionModuleImpl::notifyEventAnimCmd(int commandType, soArrayContractibleTable<acCmdArgConv> commandArgList, u8* option, soModuleAccesser* accesser) {
    if (commandType <= -1 || commandType >= 14) {
        return 0;
    }
    soArrayContractibleTable<acCmdArgConv> args(commandArgList);
    switch (commandType) {
    case 0:
    case 1:
    case 2:
    case 3: {
        s32 unitID = -1;
        s32 groupID = -1;
        s32 kind = -1;
        if (commandType == 3) {
            groupID = getFrontArg(args).getIntData();
            shiftArg(args);
            unitID = getFrontArg(args).getIntData();
            shiftArg(args);
            kind = (s16) getFrontArg(args).getIntData();
            shiftArg(args);
        } else if (commandType == 2) {
            kind = (s16) getFrontArg(args).getIntData();
            shiftArg(args);
        } else if (commandType == 0) {
            unitID = getFrontArg(args).getIntData();
            shiftArg(args);
        }
        acCmdArg arg = getFrontArg(args);
        s32 value;
        if (arg.getArgType() == 0) {
            value = arg.getIntData();
        } else if (arg.getArgType() == 5) {
            value = soValueAccesser::getValueInt(accesser, arg.getIntData(), 0);
        } else {
            return 1;
        }
        shiftArg(args);
        soTransitionTerm term;
        term.m_flags |= 0x80;
        term.m_targetKind = value;
        term.m_generalTermIndex = -1;
        u16 attr = *option;
        addTerm(groupID, &term, unitID, kind, &attr);
        addGeneralTermLastTerm(groupID, (soGeneralTerm*) &args);
        return 1;
    }
    case 4:
        addGeneralTermLastTerm(-1, (soGeneralTerm*) &args);
        return 1;
    case 5: {
        s32 groupID = getFrontArg(args).getIntData();
        shiftArg(args);
        s32 unitID = getFrontArg(args).getIntData();
        shiftArg(args);
        addGeneralTerm(groupID, unitID, (soGeneralTerm*) &args);
        return 1;
    }
    case 6:
    case 7:
    case 8:
    case 9: {
        s32 groupID = -1;
        if (commandType != 6 && commandType != 8) {
            groupID = getFrontArg(args).getIntData();
            shiftArg(args);
        }
        if (commandType == 6 || commandType == 7) {
            enableTerm(getFrontArg(args).getIntData(), groupID);
        } else {
            unableTerm(getFrontArg(args).getIntData(), groupID);
        }
        return 1;
    }
    case 10:
    case 11:
        if (commandType == 10) {
            enableTermGroup(getFrontArg(args).getIntData());
        } else {
            unableTermGroup(getFrontArg(args).getIntData());
        }
        return 1;
    case 12: {
        s32 groupID = getFrontArg(args).getIntData();
        if (groupID > -1) {
            m_groupID = groupID;
        }
        return 1;
    }
    case 13:
        clearTransitionTermAll(-1);
        return 1;
    default:
        return 0;
    }
}

soTransitionInfo* soTransitionModuleImpl::getLastTransitionInfo() {
    return &m_transitionInfo;
}

soTransitionModuleImpl::~soTransitionModuleImpl() { }
