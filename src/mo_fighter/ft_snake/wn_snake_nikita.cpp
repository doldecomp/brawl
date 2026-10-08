#include <wn/snake/wn_snake_nikita.h>

#include <gf/gf_task_scheduler.h>
#include <so/article/so_article.h>
#include <so/article/so_generate_article_manage_module.h>
#include <so/link/so_link_module_impl.h>
#include <so/work/so_work_manage_module_impl.h>
#include <so/so_external_value_accesser.h>

class wnSnakeNikitaMissile : public wnWeaponBuilder<wnSnakeNikitaMissileModuleAccesserBuildConfig> {
public:
    void setAutonomy();
};

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