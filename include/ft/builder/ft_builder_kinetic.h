#pragma once

// soKineticModuleBuilder<soKineticModuleBuildConfig<soKineticModuleGenericImpl, ...>> (0x308 bytes):
// ftMarth fn_106_66DC (ctor, 0x3D0 bytes) / fn_106_3248 (dtor).
//   soKineticModuleBuilder(soModuleAccesser*)
// Layout: soKineticModuleGenericImpl (+0x0, 0x30), soInstanceManagerFullPropertyVector<soKineticEnergy*, 12> (+0x30),
// soKineticMediatorImpl<type list> (+0xE0, 0x228) whose instance pools hold the eight energies of a fighter
// (Motion, Gravity, Controller, Stop, Damage, WindNormal, GroundMovement, Jostle).

#include <ft/builder/ft_dol_array_list.h>
#include <ft/builder/ft_builder_transition.h>
#include <ft/builder/ft_dol_types.h>
#include <ft/ft_kinetic_energy.h>
#include <so/kinetic/so_kinetic_module_impl.h>
#include <so/so_module_accesser.h>
#include <so/status/so_status_event_presenter.h>
#include <types.h>

// ---- sora_melee side -----------------------------------------------------------------------------------

typedef soInstanceManagerFullPropertyVector<soKineticEnergy*, 12> ftKineticEnergyManager;

// The module implementation lives in sora_melee (constructor), HYPOTHESIS: 0x10 bytes more than soKineticModuleImpl.
class soKineticModuleGenericImpl : public soKineticModuleImpl, public soStatusEventObserver {
public:
    soKineticModuleGenericImpl(soModuleAccesser* acc, ftKineticEnergyManager* manager, void* mediator);
    void* m_mediator; // +0x2c (HYPOTHESIS)
};

class soKineticMediator {
public:
    virtual ~soKineticMediator() { }
};

// ---- instance pool machinery ---------------------------------------------------------------------------

template <typename T, int N>
struct soInstancePoolInfo {
    typedef T Type;
};

template <int Index, int Attribute>
struct soKineticEnergyInitInfo {
    enum { EnergyIndex = Index, EnergyAttribute = Attribute };
};

template <typename E, typename Next, typename InitInfo>
class soKineticEnergyHolder {
public:
    virtual ~soKineticEnergyHolder() { }
private:
    E m_energy;
public:
    soKineticEnergyHolder(soModuleAccesser* acc) : m_energy() {
        acc->getKineticModule().addEnergy(&m_energy, InitInfo::EnergyIndex, soKineticEnergy::AttributeFlag(InitInfo::EnergyAttribute), -1);
        m_energy.disable();
    }
    E* getEnergy() { return &m_energy; }
};

template <typename E>
class soInstancePoolSubNull {
public:
};

template <typename Info, typename Holder>
class soInstancePoolSub {
public:
    virtual typename Info::Type* getInstanceAt(int index) {
        if (index == 0) {
            return m_holder.getEnergy();
        }
        return 0;
    }
private:
    soInstancePoolSubNull<typename Info::Type> m_next;
    Holder m_holder;
public:
    soInstancePoolSub(soModuleAccesser* acc) : m_holder(acc) { }
};

class soInstancePoolRoot {
public:
    soInstancePoolRoot(soModuleAccesser* acc) { }
    virtual ~soInstancePoolRoot() { }
};

template <typename Info, typename Holder, typename Base>
class soInstancePool : public Base {
    soInstancePoolSub<Info, Holder> m_sub;
public:
    soInstancePool(soModuleAccesser* acc) : Base(acc), m_sub(acc) { }

};

template <typename Info, typename Holder, typename Base>
class soLineInvertHierarchy : public soInstancePool<Info, Holder, Base> {
public:
    soLineInvertHierarchy(soModuleAccesser* acc) : soInstancePool<Info, Holder, Base>(acc) { }
    ~soLineInvertHierarchy() { }
};

// hierarchy of a one element type list (first level, based on the pool root)
template <typename Info, typename Holder>
class soLineInvertHierarchy<Info, Holder, soInstancePoolRoot> : public soInstancePool<Info, Holder, soInstancePoolRoot> {
public:
    soLineInvertHierarchy(soModuleAccesser* acc) : soInstancePool<Info, Holder, soInstancePoolRoot>(acc) { }
    ~soLineInvertHierarchy() { }
};

// ---- the energies of a fighter (index, attribute: the ids passed to soKineticModule::addEnergy) ---------------

#define FT_KINETIC_POOL(Name, Energy, Index, Attr, Base)                                                                    typedef soInstancePoolInfo<Energy, 1> Name##Info;                                                                       typedef soKineticEnergyHolder<Energy, soTypeListNullType, soKineticEnergyInitInfo<Index, Attr> > Name##Holder;          typedef soInstancePool<Name##Info, Name##Holder, Base> Name##Pool;                                                      typedef soLineInvertHierarchy<Name##Info, Name##Holder, Base> Name

typedef soInstancePoolRoot ftKineticPoolRoot;

FT_KINETIC_POOL(ftKineticPoolMotion, ftKineticEnergyMotion, 0, 1, ftKineticPoolRoot);
FT_KINETIC_POOL(ftKineticPoolGravity, ftKineticEnergyGravity, 1, 1, ftKineticPoolMotion);
FT_KINETIC_POOL(ftKineticPoolController, ftKineticEnergyController, 2, 1, ftKineticPoolGravity);
FT_KINETIC_POOL(ftKineticPoolStop, ftKineticEnergyStop, 3, 1, ftKineticPoolController);
FT_KINETIC_POOL(ftKineticPoolDamage, ftKineticEnergyDamage, 4, 2, ftKineticPoolStop);
FT_KINETIC_POOL(ftKineticPoolWind, soKineticEnergyWindNormal, 5, 4, ftKineticPoolDamage);
FT_KINETIC_POOL(ftKineticPoolGround, soKineticEnergyGroundMovement, 6, 8, ftKineticPoolWind);
FT_KINETIC_POOL(ftKineticPoolJostle, soKineticEnergyJostle, 7, 4, ftKineticPoolGround);

class ftKineticMediatorImpl : public soKineticMediator {
    ftKineticPoolJostle m_pools; // +0x4
public:
    ftKineticMediatorImpl(soModuleAccesser* acc) : soKineticMediator(), m_pools(acc) { }
    ~ftKineticMediatorImpl() { }
};

template <typename T>
class soKineticModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soKineticModuleBuilder {
    typename BC::ModuleType m_module;     // +0x0
    ftKineticEnergyManager m_manager;     // +0x30
    ftKineticMediatorImpl m_mediator;     // +0xE0
public:
    soKineticModuleBuilder(soModuleAccesser* acc) :
        m_module(acc, &m_manager, &m_mediator), m_manager(false), m_mediator(acc) { }
    soKineticModule* getModule() { return &m_module; }
};
