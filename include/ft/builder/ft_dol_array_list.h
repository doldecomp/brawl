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
#include <so/area/so_area_module_impl.h>

FT_DOL_ARRAY_VECTOR(soInterpolation<Vec3f>, 1);
FT_DOL_ARRAY_VECTOR(soCollisionAttackPart, 5);
FT_DOL_ARRAY_VECTOR(soCollisionGroup, 5);
FT_DOL_ARRAY_VECTOR(soCollisionAttackAbsolute, 2);
FT_DOL_ARRAY_VECTOR(soCollisionHitPart, 20);
FT_DOL_ARRAY_VECTOR(soCollisionGroup, 1);
FT_DOL_ARRAY_VECTOR(soCollisionHitGroup, 1);
FT_DOL_ARRAY_VECTOR(soGroundShapeImpl, 1);
FT_DOL_ARRAY_VECTOR(soCameraSubject, 1);
FT_DOL_ARRAY_VECTOR(soAreaWind, 1);
FT_DOL_ARRAY_VECTOR(soAreaContactLog, 16);
FT_DOL_ARRAY_VECTOR(soAreaInstance, 9);
FT_DOL_ARRAY_VECTOR(soShakeTerm, 4);
FT_DOL_ARRAY_VECTOR(soControllerImpl, 10);
FT_DOL_ARRAY_VECTOR(soControllerClatter, 2);
FT_DOL_ARRAY_VECTOR(soDamage, 1);
FT_DOL_ARRAY_VECTOR(soCollisionCatchPart, 4);
FT_DOL_ARRAY_VECTOR(soCollisionSearchPart, 1);
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
FT_DOL_ARRAY_VECTOR(soStatusUniqProcess*, 288);
FT_DOL_ARRAY_VECTOR(soStatusUniqProcess*, 281);
FT_DOL_ARRAY_VECTOR(soStatusUniqProcess*, 285);
FT_DOL_ARRAY_VECTOR(soCollisionHitPart, 13);
FT_DOL_ARRAY_VECTOR(soCollisionShieldPart, 1);
FT_DOL_ARRAY_VECTOR(soCollisionShieldPart, 12);
FT_DOL_ARRAY_VECTOR(soCollisionShieldPart, 15);
FT_DOL_ARRAY_VECTOR(soCollisionShieldGroup, 1);
FT_DOL_ARRAY_VECTOR(soCollisionShieldGroup, 3);
FT_DOL_ARRAY_VECTOR(soCollisionGroup, 3);
FT_DOL_ARRAY_VECTOR(soLinkConnection, 6);
FT_DOL_ARRAY_VECTOR(s32, 1);

// ft_link / ft_toonlink / ft_zelda / ft_ganon
FT_DOL_ARRAY_VECTOR(soStatusUniqProcess*, 284);
FT_DOL_ARRAY_VECTOR(soStatusUniqProcess*, 290);
FT_DOL_ARRAY_VECTOR(soCollisionShieldPart, 13);
FT_DOL_ARRAY_VECTOR(soCollisionAttackAbsolute, 10);
// ft_captain, ft_samus, ft_metaknight
FT_DOL_ARRAY_VECTOR(soStatusUniqProcess*, 301);
FT_DOL_ARRAY_VECTOR(soLinkConnection, 12);

// ft_kirby
FT_DOL_ARRAY_VECTOR(soStatusUniqProcess*, 448);
FT_DOL_ARRAY_VECTOR(soLinkConnection, 8);
FT_DOL_ARRAY_VECTOR(soCollisionShieldPart, 9);

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

// ---- kinetic energy manager (constructor in sora_melee) -----------------------------------------------------
#include <so/kinetic/so_kinetic_module_impl.h>
FT_DOL_ARRAY_VECTOR(soInstanceUnitFullProperty<soKineticEnergy*>, 12);

template <>
class soInstanceManagerFullPropertyVector<soKineticEnergy*, 12> : public soInstanceManagerFullProperty<soKineticEnergy*> {
    soArrayVector<soInstanceUnitFullProperty<soKineticEnergy*>, 12> m_arrayVector; // 0x10
    bool m_unk1;
public:
    soInstanceManagerFullPropertyVector(bool p1);
    ~soInstanceManagerFullPropertyVector() { }
    virtual soKineticEnergy*& at(s32 id);
    virtual soKineticEnergy*& atIndex(s32 idx);
    virtual s32 getId(s32 idx);
    virtual u32 size() const;
    virtual bool isContain(s32 id) const;
    virtual void erase(s32 id);
    virtual void clear();
    virtual void set(soKineticEnergy* const& elm, s32 id);
    virtual s32 add(soKineticEnergy*& elm, s32 id, soAttributeFlag attr, s16 p4);
    virtual u32 capacity();
    virtual soKineticEnergy*& atIndexFast(s32 idx);
    virtual soInstanceUnitFullProperty<soKineticEnergy*>& atUnitIndexFast(s32 idx);
    virtual s32 getIndex(s32 id) const;
    virtual void getAttributeArray(soAttributeFlag targetAttr, soArray<soKineticEnergy**>& arr);
    virtual soAttributeFlag getAttribute(s32 id) const;
    virtual void getPriorityArray(soArray<soKineticEnergy**>& arr);
};

// soArrayNull<soPhysicsIKHandle>: constructor and destructor are calls into sora_melee (used for the shared null array)
template <>
class soArrayNull<soPhysicsIKHandle> : public soArray<soPhysicsIKHandle> {
public:
    virtual bool isNull() const;
    virtual soPhysicsIKHandle& at(s32 index);
    virtual const soPhysicsIKHandle& at(s32 index) const;
    virtual s32 size() const;
    virtual ~soArrayNull();
    virtual void shift();
    virtual void pop();
    virtual void clear();
    virtual void unshift(const soPhysicsIKHandle&);
    virtual void push(const soPhysicsIKHandle&);
    virtual void insert(s32, const soPhysicsIKHandle&);
    virtual void erase(s32);
    virtual s32 capacity() const;
    virtual bool isFull() const;
    virtual void set(s32 startingIndex, const soPhysicsIKHandle& element, s32 numIndicesToSet);
    soArrayNull();
};
