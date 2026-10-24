#include <ac/ac_anim_cmd_impl.h>
#include <gf/gf_task.h>
#include <so/collision/so_collision_manager.h>
#include <so/event/so_event_manage_module_impl.h>
#include <so/event/so_event_system.h>
#include <so/so_external_value_accesser.h>
#include <so/so_module_accesser.h>
#include <so/so_value_accesser.h>
#include <so/stageobject.h>
#include <so/team/so_team_module_impl.h>

// TODO: May be generalizable beyond this file
static inline s16 getEventManageId(soModuleAccesser* accsr, soEventObserverRegistrationDesc* desc) {
    bool check = desc->checkAnimCmd();
    if (check == true) {
        soEventManager& m = static_cast<soEventManager&>(accsr->getEventManageModule());
        return m.getManageId();
    }
    return -1;
}

soTeamModuleImpl::soTeamModuleImpl(soTeam* team,
                    soTeam* hitTeam,
                    soTeam* indirectTeam,
                    soModuleAccesser* accsr,
                    soEventObserverRegistrationDesc* desc) :
        soTeamEventObserver(0),
        soAnimCmdEventObserver(5, getEventManageId(accsr, desc)),
        m_moduleAccsr(accsr),
        m_team(team),
        m_hitTeam(hitTeam),
        m_indirectTeam(indirectTeam),
        m_teamOwnerId(-1),
        m_eventPresenter(m_teamOwnerId)
{

}

soTeamModuleImpl::~soTeamModuleImpl() { }

// NONMATCHING regswaps
void soTeamModuleImpl::setTeam(s32 team, bool notify) {
    s32 i;
    s32 tid;
    s32 currTeam;
    soInstanceManagerFullProperty<soTeamEventObserver*>* list;
    if (team != m_team->getNo()) {
        currTeam = m_team->getNo();
        m_team->setNo(team);
        m_indirectTeam->setNo(team);
        if (notify == true) {
            tid = m_moduleAccsr->m_stageObject->getTaskId();
            list = m_eventPresenter.getObserverList();
            for (i = 0; i < list->size(); i++)
                list->atIndex(i)->notifyEventChangeTeam(team, currTeam, tid);
        }
    }
}

void soTeamModuleImpl::setHitTeam(s32 team) {
    if (m_hitTeam->getNo() != team)
        m_hitTeam->setNo(team);
}

void soTeamModuleImpl::setTeamOwnerId(s32 newOwnerId) {
    if (newOwnerId != 0xFFFFFFFF) {
        gfTask* task = gfTask::getTask(newOwnerId);
        if (task) {
            StageObject* stgObj = dynamic_cast<StageObject*>(task);
            if (stgObj) {
                m_teamOwnerId = soExternalValueAccesser::getTeamOwnerId(stgObj);
                s32 currTeam = getTeam()->getNo();
                s32 newTeam = soExternalValueAccesser::getTeamNo(stgObj);
                setTeam(newTeam, true);
                if (currTeam == getHitTeam()->getNo())
                    setHitTeam(newTeam);
            }
        } else {
            m_teamOwnerId = newOwnerId;
        }
    } else {
        m_teamOwnerId = newOwnerId;
    }
}

soTeam* soTeamModuleImpl::getTeam() {
    return m_team;
}

soTeam* soTeamModuleImpl::getHitTeam() {
    return m_hitTeam;
}

void soTeamModuleImpl::set2nd(s32 secnd) {
    m_team->set2nd(secnd);
    m_indirectTeam->set2nd(secnd);
}

void soTeamModuleImpl::setHit2nd(s32 secnd) {
    m_hitTeam->set2nd(secnd);
}

void soTeamModuleImpl::activate() {
    if (m_eventPresenter.m_enableOwnerEvent == true) {
        m_eventPresenter.setManageId(soCollisionManager::get()->getEventManageModule().getManageId());
        if (soTeamEventObserver::getObserverId() == -1) {
            s16 mid = soCollisionManager::get()->getEventManageModule().getManageId();
            soTeamEventObserver::addObserverSub(mid, *this, -1);
        }
    }
}

void soTeamEventObserver::addObserver(s16 manageId, s8 p2) {
    addObserverSub(manageId, *this, p2);
}

void soTeamModuleImpl::deactivate() {
    m_eventPresenter.setManageId(-1);
    if (soTeamEventObserver::getObserverId() != -1)
        soTeamEventObserver::removeObserver(soTeamEventObserver::getManageId());
}

void soTeamModuleImpl::reset() {
    m_team->reset();
    m_indirectTeam->reset();
    m_hitTeam->reset();
}

void soTeamModuleImpl::notifyEventChangeTeam(s32 newTeam, s32 _prevTeam, u32 newOwnerId) {
    if (m_teamOwnerId != 0xFFFFFFFF && m_teamOwnerId == newOwnerId)
        setTeam(newTeam, true);
}

bool soTeamModuleImpl::notifyEventAnimCmd(acAnimCmd* acmd, soModuleAccesser* accsr, s32 _p3) {
    s8 group = acmd->getGroup();
    if (!isObserv(group))
        return false;
    if (acmd->getType() <= -1 || acmd->getType() >= 3)
        return false;
    switch (acmd->getType()) {
        case 0:
        case 2: {
            s32 team;
            acCmdArg arg;
            if (!acmd->getArg(&arg, 0))
                return true;
            if (arg.getArgType() == 0)
                team = arg.getIntData();
            else if (arg.getArgType() == 5)
                team = soValueAccesser::getValueInt(accsr, arg.getValueIndexData());
            else
                return true;
            if (acmd->getType() == 2)
                setHitTeam(team);
            else
                setTeam(team, true);
            return true;
        }
        case 1: {
            s32 ownerId;
            acCmdArg arg;
            if (!acmd->getArg(&arg, 0))
                return true;
            if (arg.getArgType() == 0)
                ownerId = arg.getIntData();
            else if (arg.getArgType() == 5)
                ownerId = soValueAccesser::getValueInt(accsr, arg.getValueIndexData());
            else
                return true;
            setTeamOwnerId(ownerId);
            return true;
        }
        default:
            break;
    }
    return false;
}

// TODO name constant
bool soTeamModuleImpl::isObserv(char p1) {
    return p1 == 34;
}

void soTeamModuleImpl::setEnableOwnerEvent(bool enable) {
    m_eventPresenter.m_enableOwnerEvent = enable;
}

s32 soTeamModuleImpl::getTeamOwnerId() {
    return m_teamOwnerId;
}

soTeam* soTeamModuleImpl::getIndirectTeam() {
    return m_indirectTeam;
}
