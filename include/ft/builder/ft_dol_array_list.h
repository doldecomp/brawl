#pragma once

// The complete list of soArrayVector<T, C> instances that the fighter RELs take from sora_melee.
// MUST be included before any header instantiates one of these (e.g. soCollisionSearchModuleImpl has a
// soArrayVector<soCollisionGroup, 1> member), so ft_fighter_builder.h includes it first.
// Add new (T, C) pairs here (a duplicate is a "class redefined" error).

#include <ft/builder/ft_dol_instances.h>
#include <ft/builder/ft_dol_types.h>
#include <so/collision/so_collision_group.h>
#include <so/collision/so_collision_attack_part.h>
#include <so/collision/so_collision_hit_part.h>
#include <so/collision/so_collision_hit_group.h>
#include <so/collision/so_collision_shield_group.h>
#include <so/model/so_model_virtual_node.h>
#include <so/ground/so_ground_shape_impl.h>
#include <so/camera/so_camera_subject.h>
#include <so/damage/so_damage.h>
#include <so/controller/so_controller_impl.h>
#include <so/link/so_link_connection_server.h>
class BaseItem;
#include <so/item/so_item_pick_transactor_impl.h>
#include <ef/ef_screen_handle.h>
#include <so/posture/so_posture_module_impl.h>
#include <so/transition/so_transition_module_impl.h>
#include <so/status/so_status_module_impl.h>

FT_DOL_ARRAY_VECTOR(soInterpolation<Vec3f>, 1);
FT_DOL_ARRAY_VECTOR(soCollisionAttackPart, 5);
FT_DOL_ARRAY_VECTOR(soCollisionGroup, 5);
FT_DOL_ARRAY_VECTOR(soCollisionAttackAbsolute, 2);
FT_DOL_ARRAY_VECTOR(soCollisionHitPart, 20);
FT_DOL_ARRAY_VECTOR(soCollisionGroup, 1);
FT_DOL_ARRAY_VECTOR(soCollisionHitGroup, 1);
FT_DOL_ARRAY_VECTOR(soGroundShapeImpl, 1);
FT_DOL_ARRAY_VECTOR(soCameraSubject, 1);
FT_DOL_ARRAY_VECTOR(soShakeTerm, 4);
FT_DOL_ARRAY_VECTOR(soControllerImpl, 10);
FT_DOL_ARRAY_VECTOR(soControllerClatter, 2);
FT_DOL_ARRAY_VECTOR(soDamage, 1);
FT_DOL_ARRAY_VECTOR(soCollisionCatchPart, 4);
FT_DOL_ARRAY_VECTOR(soCollisionShieldPart, 2);
FT_DOL_ARRAY_VECTOR(soCollisionShieldPart, 20);
FT_DOL_ARRAY_VECTOR(soCollisionShieldGroup, 2);
FT_DOL_ARRAY_VECTOR(soCollisionGroup, 2);
FT_DOL_ARRAY_VECTOR(soLinkConnection, 7);
FT_DOL_ARRAY_VECTOR(soPhysicsIKHandle, 2);
FT_DOL_ARRAY_VECTOR(soItemInfo, 3);
FT_DOL_ARRAY_VECTOR(soItemInfo, 4);
FT_DOL_ARRAY_VECTOR(soEffectContinual, 1);
FT_DOL_ARRAY_VECTOR(soEffectTime, 1);
FT_DOL_ARRAY_VECTOR(efScreenHandle, 1);
FT_DOL_ARRAY_VECTOR(u32, 1);
FT_DOL_ARRAY_VECTOR(soInstanceUnitFullProperty<soTransitionTerm>, 1);
FT_DOL_ARRAY_VECTOR(soInstanceUnitFullProperty<soTransitionTerm>, 2);
FT_DOL_ARRAY_VECTOR(soInstanceUnitFullProperty<soTransitionTerm>, 3);
FT_DOL_ARRAY_VECTOR(soInstanceUnitFullProperty<soTransitionTerm>, 6);
FT_DOL_ARRAY_VECTOR(soInstanceUnitFullProperty<soTransitionTerm>, 8);
FT_DOL_ARRAY_VECTOR(soInstanceUnitFullProperty<soTransitionTerm>, 17);
FT_DOL_ARRAY_VECTOR(soInstanceUnitFullProperty<soTransitionTerm>, 25);
FT_DOL_ARRAY_VECTOR(soTransitionTermGroup, 20);
FT_DOL_ARRAY_VECTOR(soStatusUniqProcess*, 289);
FT_DOL_ARRAY_VECTOR(s32, 1);

// soArrayContractibleTable<const soStatusData>: the (table, size) constructor and the destructor are calls into sora_melee.
template <>
class soArrayContractibleTable<const soStatusData> : public soArrayContractible<const soStatusData>,
                                                     public soConnectable<soArrayContractibleTable<const soStatusData> > {
    const soStatusData* m_elements;
    s32 m_size;
public:
    soArrayContractibleTable() : m_elements(nullptr), m_size(0) { }
    soArrayContractibleTable(const soStatusData* elements, s32 size);
    virtual ~soArrayContractibleTable();
    virtual const soStatusData& at(s32 index);
    virtual const soStatusData& at(s32 index) const;
    virtual void shift();
    virtual void pop();
    virtual void clear();
    virtual s32 size() const;
    virtual bool isNull() const;
    virtual const soStatusData& atSub(s32 index) const;
};
