#pragma once

#include <so/so_array.h>
#include <so/event/so_event_manage_module_impl.h>
#include <so/event/so_event_system.h>
#include <so/so_instance_manager.h>
#include <so/so_instance_unit.h>
#include <so/template_utils.h>
#include <types.h>

// For the EventObserver classes referenced by soInsideEventManageModuleBuilder
#include <so/status/so_status_event_presenter.h>
#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/damage/so_damage_event_presenter.h>
#include <so/link/so_link_event_presenter.h>
#include <so/situation/so_situation_event_presenter.h>
#include <so/collision/so_collision_hit_event_presenter.h>
#include <so/collision/so_collision_attack_event_presenter.h>
#include <so/model/so_model_event_presenter.h>
#include <so/article/so_article.h>
#include <so/capture/so_capture_event_presenter.h>
#include <so/collision/so_collision_shield_event_presenter_shield.h>
#include <so/collision/so_collision_shield_event_presenter_reflector.h>
#include <so/collision/so_collision_shield_event_presenter_absorber.h>
#include <so/collision/so_collision_search_event_presenter.h>
#include <so/item/so_item_manage_event_presenter.h>
#include <so/motion/so_motion_event_presenter.h>
#include <so/event/so_gimmick_event_presenter.h>
#include <so/turn/so_turn_event_presenter.h>
#include <so/collision/so_collision_catch_event_presenter.h>

struct wnInsideEventManageModuleTypes {
    enum {
        hasStatus = true,
        hasAnimCmd = true,
        hasDamage = true,
        hasLink = true,
        hasSituation = true,
        hasCollisionHit = true,
        hasCollisionAttack = true,
        hasModel = true,
        hasArticle = true,
        hasCapture = true,
        hasCollisionShield = true,
        hasCollisionReflector = true,
        hasCollisionAbsorber = true,
        hasCollisionSearch = true,
        hasItemManage = true,
        hasMotion = true,
        hasGimmick = true,
        hasTurn = true,
        hasCollisionCatch = true,
    };
};

// Identical to wnInsideEventManageModuleTypes, except hasGimmick is false
struct ftInsideEventManageModuleTypes {
    enum {
        hasStatus = true,
        hasAnimCmd = true,
        hasDamage = true,
        hasLink = true,
        hasSituation = true,
        hasCollisionHit = true,
        hasCollisionAttack = true,
        hasModel = true,
        hasArticle = true,
        hasCapture = true,
        hasCollisionShield = true,
        hasCollisionReflector = true,
        hasCollisionAbsorber = true,
        hasCollisionSearch = true,
        hasItemManage = true,
        hasMotion = true,
        hasGimmick = false,
        hasTurn = true,
        hasCollisionCatch = true,
    };
};

template<typename Obsvr, bool IsPresent, u32 Cap>
struct GetEventUnit {
    struct GetUnitHelper {
        typedef typename soSelect<Cap != 0,
                                    soEventUnitWithWorkArea<Obsvr, Cap>,
                                    soEventUnitNull<Obsvr> >::Result Type;
    };

    typedef typename soSelect<IsPresent, typename GetUnitHelper::Type, void*>::Result Type;
};

template<u32 C1, u32 C2, u32 C3, u32 C4, u32 C5,
         u32 C6, u32 C7, u32 C8, u32 C9, u32 C10,
         u32 C11, u32 C12, u32 C13, u32 C14, u32 C15,
         u32 C16, u32 C17, u32 C18, u32 C19, typename T>
class soInsideEventManageModuleBuildConfig {
public:
    // The capacities of the observer lists comprising the
    // soInsideEventManageModuleBuilder, as selected according to the
    // instantiation of this build configuration template
    enum {
        StatusCap = C1,
        AnimCmdCap = C2,
        DamageCap = C3,
        LinkCap = C4,
        SituationCap = C5,
        CollisionHitCap = C6,
        CollisionAttackCap = C7,
        ModelCap = C8,
        ArticleCap = C9,
        CaptureCap = C10,
        CollisionShieldCap = C11,
        CollisionReflectorCap = C12,
        CollisionAbsorberCap = C13,
        CollisionSearchCap = C14,
        ItemManageCap = C15,
        MotionCap = C16,
        GimmickCap = C17,
        TurnCap = C18,
        CollisionCatchCap = C19,
    };

    // The event IDs of each kind of EventObserver, which are apparently
    // fixed across all build configurations
    enum {
        StatusEvtId = 4,
        AnimCmdEvtId = 5,
        DamageEvtId = 6,
        LinkEvtId = 7,
        SituationEvtId = 8,
        CollisionHitEvtId = 0,
        CollisionAttackEvtId = 1,
        ModelEvtId = 9,
        ArticleEvtId = 11,
        CaptureEvtId = 13,
        CollisionShieldEvtId = 14,
        CollisionReflectorEvtId = 15,
        CollisionAbsorberEvtId = 16,
        CollisionSearchEvtId = 17,
        ItemManageEvtId = 12,
        MotionEvtId = 10,
        GimmickEvtId = 3,
        TurnEvtId = 18,
        CollisionCatchEvtId = 2,
    };
};

#define soInsideEventManageModuleBuilder_MEMBER_LIST \
    soInstanceManagerSimpleEntity<soEventUnit*, soArrayVector<soInstanceUnit<soEventUnit*>, 19> > m_entity;                                 \
    soEventManageModuleImpl m_module;                                                                                                       \
    typename GetEventUnit<soStatusEventObserver, T::hasStatus, B::StatusCap>::Type m_status;                                                \
    typename GetEventUnit<soAnimCmdEventObserver, T::hasAnimCmd, B::AnimCmdCap>::Type m_animCmd;                                            \
    typename GetEventUnit<soDamageEventObserver, T::hasDamage, B::DamageCap>::Type m_damage;                                                \
    typename GetEventUnit<soLinkEventObserver, T::hasLink, B::LinkCap>::Type m_link;                                                        \
    typename GetEventUnit<soSituationEventObserver, T::hasSituation, B::SituationCap>::Type m_situation;                                    \
    typename GetEventUnit<soCollisionHitEventObserver, T::hasCollisionHit, B::CollisionHitCap>::Type m_collisionHit;                        \
    typename GetEventUnit<soCollisionAttackEventObserver, T::hasCollisionAttack, B::CollisionAttackCap>::Type m_collisionAttack;            \
    typename GetEventUnit<soModelEventObserver, T::hasModel, B::ModelCap>::Type m_model;                                                    \
    typename GetEventUnit<soArticleEventObserver, T::hasArticle, B::ArticleCap>::Type m_article;                                            \
    typename GetEventUnit<soCaptureEventObserver, T::hasCapture, B::CaptureCap>::Type m_capture;                                            \
    typename GetEventUnit<soCollisionShieldEventObserver, T::hasCollisionShield, B::CollisionShieldCap>::Type m_collisionShield;            \
    typename GetEventUnit<soCollisionReflectorEventObserver, T::hasCollisionReflector, B::CollisionReflectorCap>::Type m_collisionReflector;\
    typename GetEventUnit<soCollisionAbsorberEventObserver, T::hasCollisionAbsorber, B::CollisionAbsorberCap>::Type m_collisionAbsorber;    \
    typename GetEventUnit<soCollisionSearchEventObserver, T::hasCollisionSearch, B::CollisionSearchCap>::Type m_collisionSearch;            \
    typename GetEventUnit<soItemManageEventObserver, T::hasItemManage, B::ItemManageCap>::Type m_itemManage;                                \
    typename GetEventUnit<soMotionEventObserver, T::hasMotion, B::MotionCap>::Type m_motion;                                                \
    typename GetEventUnit<soGimmickEventObserver, T::hasGimmick, B::GimmickCap>::Type m_gimmick;                                            \
    typename GetEventUnit<soTurnEventObserver, T::hasTurn, B::TurnCap>::Type m_turn;                                                        \
    typename GetEventUnit<soCollisionCatchEventObserver, T::hasCollisionCatch, B::CollisionCatchCap>::Type m_collisionCatch;

template<typename B, typename T>
class soInsideEventManageModuleBuilder {
    soInsideEventManageModuleBuilder_MEMBER_LIST
public:
    soInsideEventManageModuleBuilder() :
        m_entity(),
        m_module(this),
        m_status(m_module.getManageId(), B::StatusEvtId),
        m_animCmd(m_module.getManageId(), B::AnimCmdEvtId),
        m_damage(m_module.getManageId(), B::DamageEvtId),
        m_link(m_module.getManageId(), B::LinkEvtId),
        m_situation(m_module.getManageId(), B::SituationEvtId),
        m_collisionHit(m_module.getManageId(), B::CollisionHitEvtId),
        m_collisionAttack(m_module.getManageId(), B::CollisionAttackEvtId),
        m_model(m_module.getManageId(), B::ModelEvtId),
        m_article(m_module.getManageId(), B::ArticleEvtId),
        m_capture(m_module.getManageId(), B::CaptureEvtId),
        m_collisionShield(m_module.getManageId(), B::CollisionShieldEvtId),
        m_collisionReflector(m_module.getManageId(), B::CollisionReflectorEvtId),
        m_collisionAbsorber(m_module.getManageId(), B::CollisionAbsorberEvtId),
        m_collisionSearch(m_module.getManageId(), B::CollisionSearchEvtId),
        m_itemManage(m_module.getManageId(), B::ItemManageEvtId),
        m_motion(m_module.getManageId(), B::MotionEvtId),
        m_gimmick(m_module.getManageId(), B::GimmickEvtId),
        m_turn(m_module.getManageId(), B::TurnEvtId),
        m_collisionCatch(m_module.getManageId(), B::CollisionCatchEvtId) { }

    ~soInsideEventManageModuleBuilder() { }
    soEventManageModuleImpl* getModule() { return &m_module; }
};

template<typename B>
class soInsideEventManageModuleBuilder<B, ftInsideEventManageModuleTypes> {
    typedef ftInsideEventManageModuleTypes T;
    soInsideEventManageModuleBuilder_MEMBER_LIST
public:
    // Note that this specialized constructor leaves out the initializer
    // for m_gimmick
    soInsideEventManageModuleBuilder() :
        m_entity(),
        m_module(this),
        m_status(m_module.getManageId(), B::StatusEvtId),
        m_animCmd(m_module.getManageId(), B::AnimCmdEvtId),
        m_damage(m_module.getManageId(), B::DamageEvtId),
        m_link(m_module.getManageId(), B::LinkEvtId),
        m_situation(m_module.getManageId(), B::SituationEvtId),
        m_collisionHit(m_module.getManageId(), B::CollisionHitEvtId),
        m_collisionAttack(m_module.getManageId(), B::CollisionAttackEvtId),
        m_model(m_module.getManageId(), B::ModelEvtId),
        m_article(m_module.getManageId(), B::ArticleEvtId),
        m_capture(m_module.getManageId(), B::CaptureEvtId),
        m_collisionShield(m_module.getManageId(), B::CollisionShieldEvtId),
        m_collisionReflector(m_module.getManageId(), B::CollisionReflectorEvtId),
        m_collisionAbsorber(m_module.getManageId(), B::CollisionAbsorberEvtId),
        m_collisionSearch(m_module.getManageId(), B::CollisionSearchEvtId),
        m_itemManage(m_module.getManageId(), B::ItemManageEvtId),
        m_motion(m_module.getManageId(), B::MotionEvtId),
        m_turn(m_module.getManageId(), B::TurnEvtId),
        m_collisionCatch(m_module.getManageId(), B::CollisionCatchEvtId) { }

    ~soInsideEventManageModuleBuilder() { }
};
