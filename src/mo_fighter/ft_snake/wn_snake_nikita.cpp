#include <wn/snake/wn_snake_nikita.h>

#include <so/kinetic/so_kinetic_module_impl.h>
#include <wn/snake/so_kinetic_energy_local_normal.h>

#include <gf/gf_task_scheduler.h>
#include <so/article/so_article.h>
#include <so/article/so_generate_article_manage_module.h>
#include <so/link/so_link_module_impl.h>
#include <so/work/so_work_manage_module_impl.h>
#include <so/so_external_value_accesser.h>

class wnSnakeNikitaMissile
    : public wnWeaponBuilder<wnSnakeNikitaMissileModuleAccesserBuildConfig>,
      public soDamageEventObserver,
      public soCollisionSearchEventObserver {
public:
    void setAutonomy();
    virtual void processCollision();
    virtual void notifyEventCollisionSearch(soCollisionLog* collisionLog,
                                            soModuleAccesser* moduleAccesser);
    virtual bool notifyEventCollisionSearchCheck();
    virtual bool notifyEventCollisionAttackCheck(u32 flags);
};
static_assert(sizeof(wnSnakeNikitaMissile) == 0x2510,
              "Snake Nikita missile builder and observer layout");

namespace {
soGenerateArticleManageModule& getArticleManage(soModuleAccesser& accesser) {
    // HYPOTHESIS: this builder accessor stores the article manager at the
    // verified module-enumeration slot +0x84.
    return *static_cast<soGenerateArticleManageModule*>(
        accesser.m_enumerationStart->m_generateArticleManageModule);
}

struct SnakeNikitaEndEvent : soLinkEventArgs {
    explicit SnakeNikitaEndEvent(int eventKind) : soLinkEventArgs(eventKind) { }
};
}

void wnSnakeNikitaMissile::setAutonomy() {
    m_moduleAccesser->getWorkManageModule().onFlag(0x12000003);

    if (m_moduleAccesser->getLinkModule().isLink(3)) {
        // HYPOTHESIS: the enum names attribute 4 as unknown; its meaning is unverified.
        m_moduleAccesser->getLinkModule().setAttribute(
            3, soLinkConnection::Attribute_Reference_Parent_Unknown_4, false);
    }
}

void wnSnakeNikita::notifyEventLink(soLinkEventArgs* eventInfo,
                                    soModuleAccesser* moduleAccesser,
                                    StageObject* linkedObject, int unk4) {
    switch (eventInfo->m_eventKind) {
    case 0x838:
        notifyEnd(1);
        break;
    case 0x839:
        notifyEnd(0);
        break;
    default:
        break;
    }

    Weapon::notifyEventLink(eventInfo, moduleAccesser, linkedObject, unk4);
}

void wnSnakeNikita::notifyEnd(int isEnd) {
    if (isEnd != 0) {
        SnakeNikitaEndEvent event(0x456);
        m_moduleAccesser->getLinkModule().sendEventParents(3, event);
    } else {
        SnakeNikitaEndEvent event(0x457);
        m_moduleAccesser->getLinkModule().sendEventParents(3, event);
    }
}

void wnSnakeNikita::onDeactivate() {
    soArrayVector<soArticle*, 3> articles;
    getArticleManage(*m_moduleAccesser).getArticleList(&articles, 0, 2);

    if (!articles.isNull()) {
        wnSnakeNikitaMissile* missile =
            dynamic_cast<wnSnakeNikitaMissile*>(articles.at(0));
        if (missile != nullptr) {
            missile->setAutonomy();

            const unsigned long taskId = *reinterpret_cast<u32*>(
                reinterpret_cast<u8*>(missile) + 0x28);
            bool alreadyTracked = false;
            for (s32 index = 0; index < m_unkMissileTaskIds.size(); ++index) {
                if (m_unkMissileTaskIds.at(index) == taskId) {
                    alreadyTracked = true;
                }
            }
            if (!alreadyTracked) {
                m_unkMissileTaskIds.push(taskId);
            }
        }
    }
}

void wnSnakeNikita::forceFallMissile() {
    soArrayVector<soArticle*, 3> articles;
    getArticleManage(*m_moduleAccesser).getArticleList(&articles, 0, 2);

    if (!articles.isNull()) {
        wnSnakeNikitaMissile* missile =
            dynamic_cast<wnSnakeNikitaMissile*>(articles.at(0));
        if (missile != nullptr && soExternalValueAccesser::getStatusKind(missile) == 0 &&
            !soExternalValueAccesser::getWorkFlag(missile, 0x12000003)) {
            missile->changeStatus(1);
        }
    }
}

void wnSnakeNikitaMissile::processCollision() {
    const int statusKind = m_moduleAccesser->getStatusModule().getStatusKind();
    if (statusKind == 0) {
        m_moduleAccesser->getWorkManageModule().offFlag(0x22000001);
    } else if (statusKind == 1) {
        m_moduleAccesser->getWorkManageModule().offFlag(0x22000000);
    }
    StageObject::processCollision();
}

void wnSnakeNikitaMissile::notifyEventCollisionSearch(
    soCollisionLog* collisionLog, soModuleAccesser*) {
    if (collisionLog == nullptr) {
        return;
    }

    const int statusKind = m_moduleAccesser->getStatusModule().getStatusKind();
    soWorkManageModule& work = m_moduleAccesser->getWorkManageModule();
    if (statusKind == 0) {
        if (collisionLog->_33 != 3) {
            work.onFlag(0x22000001);
        } else if (collisionLog->m_teamNo !=
                   soExternalValueAccesser::getTeamNo(this) &&
                   m_moduleAccesser->getReflectModule().isCountMax()) {
            work.onFlag(0x22000002);
        }
    } else if (statusKind == 1) {
        if (collisionLog->_33 != 3) {
            work.onFlag(0x22000000);
        } else if (collisionLog->m_teamNo !=
                   soExternalValueAccesser::getTeamNo(this)) {
            work.onFlag(0x22000001);
        }
    }
}

bool wnSnakeNikitaMissile::notifyEventCollisionSearchCheck() {
    soWorkManageModule& work = m_moduleAccesser->getWorkManageModule();
    const int statusKind = m_moduleAccesser->getStatusModule().getStatusKind();
    bool shouldReflect = false;
    if (statusKind == 0) {
        shouldReflect = work.isFlag(0x22000002);
        if (shouldReflect) {
            work.offFlag(0x22000002);
        }
    } else if (statusKind == 1) {
        shouldReflect = work.isFlag(0x22000001);
        if (shouldReflect) {
            work.offFlag(0x22000001);
        }
    }

    if (shouldReflect) {
        setAutonomy();
        SnakeNikitaEndEvent event(0x839);
        m_moduleAccesser->getLinkModule().sendEventParents(3, event);

        const int team = m_moduleAccesser->getReflectModule().getTeam();
        m_moduleAccesser->getTeamModule().setTeam(team, true);
        m_moduleAccesser->getTeamModule().setHitTeam(team);

        soKineticEnergyLocalNormal* energy = dynamic_cast<soKineticEnergyLocalNormal*>(
            m_moduleAccesser->getKineticModule().getEnergy(2));
        if (energy != nullptr) {
            energy->unk34 -= 0.3846154f;
            if (energy->unk34 < 0.0f) {
                energy->unk34 += 360.0f;
            }
            Vec3f rotation(-energy->unk34, 90.0f, 0.0f);
            m_moduleAccesser->getPostureModule().setRot(&rotation, 1);
        }
        return false;
    }

    // HYPOTHESIS: these two work flags represent the native status-specific
    // collision transition gates; the flags themselves remain unnamed.
    if (statusKind == 0 && work.isFlag(0x22000001)) {
        m_moduleAccesser->getStatusModule().changeStatusRequest(2, m_moduleAccesser);
        return true;
    }
    if (statusKind == 1 && work.isFlag(0x22000000)) {
        m_moduleAccesser->getStatusModule().changeStatusRequest(2, m_moduleAccesser);
        return true;
    }
    return false;
}

bool wnSnakeNikitaMissile::notifyEventCollisionAttackCheck(u32 flags) {
    // HYPOTHESIS: native rlwinm tests the two low-order mask bits (0x6).
    if ((flags & 0x6) == 0) {
        Weapon::notifyEventCollisionAttackCheck(flags);
    }
    return false;
}
