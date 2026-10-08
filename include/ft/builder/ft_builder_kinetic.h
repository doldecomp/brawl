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

// sora_melee: the fighter specific part of the mediator work. HYPOTHESIS: parameter types.
class ftKineticTransactor {
public:
    static void changeKinetic(soModuleAccesser* acc, void* pools);
    static void addSpeed(void* speed, void* pools, soModuleAccesser* acc);
    static void addSpeedOutside(int type, void* speed, void* pools, soModuleAccesser* acc);
    static void notifyEventChangeStatus(void* a, void* b, void* c, void* d);
    template <typename E>
    static void updateEnergy(E* energy, soModuleAccesser* acc) {
        if (energy->isEnable() != true) {
            return;
        }
        if (energy->isSuspend()) {
            return;
        }
        return energy->updateEnergy(acc);
    }
};

class soKineticTransactHelper {
public:
    static void checkClearSpeed(soKineticEnergy* energy);
};

// HYPOTHESIS: the energy attribute mask as seen by the mediator (signed 16 bit, user destructor).
struct soKineticAttributeMask {
    s16 m_mask;
    soKineticAttributeMask(s16 mask) : m_mask(mask) { }
    ~soKineticAttributeMask() { }
};

template <typename Transactor>
class soKineticUpdateEnergyHolderHelper {
public:
    typedef Transactor TransactorType;
    soKineticAttributeMask m_flag;
    soKineticUpdateEnergyHolderHelper(soKineticAttributeMask flag) : m_flag(flag) { }
};

// Interface of the mediator (vtable at the start of soKineticMediatorImpl); there is no virtual destructor.
class soKineticMediator {
public:
    virtual void changeKinetic(soModuleAccesser* acc) = 0;
    virtual void updateEnergy(soModuleAccesser* acc) = 0;
    virtual void updateEnergy1(soModuleAccesser* acc, soKineticAttributeMask flag) = 0;
    virtual void updateEnergy2(soArray<soKineticEnergy**>* energies, soModuleAccesser* acc) = 0;
    virtual void postUpdateEnergy() = 0;
    virtual void addSpeed(void* speed, soModuleAccesser* acc) = 0;
    virtual void addSpeedOutside(int type, void* speed, soModuleAccesser* acc) = 0;
    virtual void notifyEventChangeStatus(void* a, void* b, void* c, void* d) = 0;
    virtual int getMediateNum() = 0;
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
    enum { Attribute = InitInfo::EnergyAttribute };
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
    template <typename Helper>
    int forEachHolderModuleAccesser(Helper helper, soModuleAccesser* acc) {
        return 0;
    }
};

template <typename Info, typename Holder>
class soInstancePoolSub {
public:
    virtual ~soInstancePoolSub() { }
private:
    soInstancePoolSubNull<typename Info::Type> m_next;
    Holder m_holder;
public:
    soInstancePoolSub(soModuleAccesser* acc) : m_holder(acc) { }
    typename Info::Type* getInstanceAt(int index) {
        if (index == 0) {
            return m_holder.getEnergy();
        }
        return 0;
    }
    template <typename Helper>
    int forEachHolderModuleAccesser(Helper helper, soModuleAccesser* acc) {
        typename Info::Type* energy = m_holder.getEnergy();
        if ((helper.m_flag.m_mask & Holder::Attribute) && energy->isEnable() == true && !energy->isSuspend()) {
            Helper::TransactorType::updateEnergy(energy, acc);
        }
        return m_next.forEachHolderModuleAccesser(helper, acc);
    }
};

class soInstancePoolRoot {
public:
    soInstancePoolRoot(soModuleAccesser* acc) { }
    virtual ~soInstancePoolRoot() { }
    template <typename Helper>
    int forEachHolderModuleAccesser(const Helper&, soModuleAccesser*) { return 0; }
};

template <typename Info, typename Holder, typename Base>
class soInstancePool : public Base {
    soInstancePoolSub<Info, Holder> m_sub;
public:
    soInstancePool(soModuleAccesser* acc) : Base(acc), m_sub(acc) { }
    soInstancePoolSub<Info, Holder>& getSub() { return m_sub; }
    template <typename Helper>
    int forEachHolderModuleAccesser(const Helper& helper, soModuleAccesser* acc) {
        m_sub.forEachHolderModuleAccesser(helper, acc);
        return Base::forEachHolderModuleAccesser(helper, acc);
    }

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
    ~soLineInvertHierarchy() __attribute__((never_inline)) { } // MATCH-ONLY: shared first-level teardown.
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

#define FT_KINETIC_EACH_POOL(M) M(Jostle) M(Ground) M(Wind) M(Damage) M(Stop) M(Controller) M(Gravity) M(Motion)
#define FT_KINETIC_SUB(L) static_cast<ftKineticPool##L##Pool&>(m_pools).getSub()


class ftKineticMediatorImpl : public soKineticMediator {
    ftKineticPoolJostle m_pools; // +0x4
public:
    ftKineticMediatorImpl(soModuleAccesser* acc) : m_pools(acc) { }
    ~ftKineticMediatorImpl() { }

#define FT_KINETIC_CLEAR(L)                                                                                               for (int i = 0; i < 1; i++) {                                                                                             soKineticTransactHelper::checkClearSpeed(FT_KINETIC_SUB(L).getInstanceAt(i));                                      }
    virtual void changeKinetic(soModuleAccesser* acc) {
        ftKineticTransactor::changeKinetic(acc, &m_pools);
        FT_KINETIC_EACH_POOL(FT_KINETIC_CLEAR)
    }

#define FT_KINETIC_UPDATE(L)                                                                                              for (int i = 0; i < 1; i++) {                                                                                             ftKineticPool##L##Info::Type* energy = FT_KINETIC_SUB(L).getInstanceAt(i);                                             if (energy->isEnable() == true && !energy->isSuspend()) {                                                                  ftKineticTransactor::updateEnergy(energy, acc);                                                                    }                                                                                                                  }
    virtual void updateEnergy(soModuleAccesser* acc) {
        FT_KINETIC_EACH_POOL(FT_KINETIC_UPDATE)
    }

    virtual void updateEnergy1(soModuleAccesser* acc, soKineticAttributeMask flag) {
        soKineticUpdateEnergyHolderHelper<ftKineticTransactor> helper(flag);
        m_pools.forEachHolderModuleAccesser(helper, acc);
    }

    virtual void updateEnergy2(soArray<soKineticEnergy**>* energies, soModuleAccesser* acc) {
        for (int i = 0; i < energies->size(); i++) {
            soKineticEnergy* energy = **&energies->at(i);
            if (energy->isEnable() != false && energy->isSuspend() != true) {
                if (energy->isEnable() == true && energy->isSuspend() == false) {
                    if (energy->isEnable() == true && energy->isSuspend() == false) {
                        energy->updateEnergy(acc);
                    }
                }
            }
        }
    }

    virtual void postUpdateEnergy() { }
    virtual void addSpeed(void* speed, soModuleAccesser* acc) { ftKineticTransactor::addSpeed(speed, &m_pools, acc); }
    virtual void addSpeedOutside(int type, void* speed, soModuleAccesser* acc) { ftKineticTransactor::addSpeedOutside(type, speed, &m_pools, acc); }
    virtual void notifyEventChangeStatus(void* a, void* b, void* c, void* d) { ftKineticTransactor::notifyEventChangeStatus(a, b, c, d); }
    virtual int getMediateNum() { return 8; }
};

// ftXxxKineticTransactor of a fighter (changeKinetic is in the fighter REL, the rest is the ftKineticTransactor in sora_melee).
#define FT_KINETIC_TRANSACTOR(Name)                                                                                       class Name : public ftKineticTransactor {                                                                                 public:                                                                                                                       static void changeKinetic(soModuleAccesser* acc, void* pools);                                                         template <typename E>                                                                                                   static void updateEnergy(E* energy, soModuleAccesser* acc) {                                                                if (energy->isEnable() != true) {                                                                                           return;                                                                                                             }                                                                                                                       if (energy->isSuspend()) {                                                                                                  return;                                                                                                             }                                                                                                                       return energy->updateEnergy(acc);                                                                                   }                                                                                                                   }

// The mediator of the fighters with their own ftXxxKineticTransactor (derived from ftKineticTransactor, with its own
// changeKinetic and updateEnergy<E> instances). Same code as ftKineticMediatorImpl.
template <typename Transactor, typename UpdateTransactor = Transactor>
class ftKineticMediatorImplT : public soKineticMediator {
    ftKineticPoolJostle m_pools; // +0x4
public:
    ftKineticMediatorImplT(soModuleAccesser* acc) : m_pools(acc) { }
    ~ftKineticMediatorImplT() { }

#undef FT_KINETIC_CLEAR
#define FT_KINETIC_CLEAR(L)                                                                                               for (int i = 0; i < 1; i++) {                                                                                             soKineticTransactHelper::checkClearSpeed(FT_KINETIC_SUB(L).getInstanceAt(i));                                      }
    virtual void changeKinetic(soModuleAccesser* acc) {
        Transactor::changeKinetic(acc, &m_pools);
        FT_KINETIC_EACH_POOL(FT_KINETIC_CLEAR)
    }

#undef FT_KINETIC_UPDATE
#define FT_KINETIC_UPDATE(L)                                                                                              for (int i = 0; i < 1; i++) {                                                                                             ftKineticPool##L##Info::Type* energy = FT_KINETIC_SUB(L).getInstanceAt(i);                                             if (energy->isEnable() == true && !energy->isSuspend()) {                                                                  UpdateTransactor::updateEnergy(energy, acc);                                                                    }                                                                                                                  }
    virtual void updateEnergy(soModuleAccesser* acc) {
        FT_KINETIC_EACH_POOL(FT_KINETIC_UPDATE)
    }

    virtual void updateEnergy1(soModuleAccesser* acc, soKineticAttributeMask flag) {
        soKineticUpdateEnergyHolderHelper<UpdateTransactor> helper(flag);
        m_pools.forEachHolderModuleAccesser(helper, acc);
    }

    virtual void updateEnergy2(soArray<soKineticEnergy**>* energies, soModuleAccesser* acc) {
        for (int i = 0; i < energies->size(); i++) {
            soKineticEnergy* energy = **&energies->at(i);
            if (energy->isEnable() != false && energy->isSuspend() != true) {
                if (energy->isEnable() == true && energy->isSuspend() == false) {
                    if (energy->isEnable() == true && energy->isSuspend() == false) {
                        energy->updateEnergy(acc);
                    }
                }
            }
        }
    }

    virtual void postUpdateEnergy() { }
    virtual void addSpeed(void* speed, soModuleAccesser* acc) { UpdateTransactor::addSpeed(speed, &m_pools, acc); }
    virtual void addSpeedOutside(int type, void* speed, soModuleAccesser* acc) { UpdateTransactor::addSpeedOutside(type, speed, &m_pools, acc); }
    virtual void notifyEventChangeStatus(void* a, void* b, void* c, void* d) { UpdateTransactor::notifyEventChangeStatus(a, b, c, d); }
    virtual int getMediateNum() { return 8; }
};

template <typename T>
class soKineticModuleBuildConfig {
public:
    typedef T ModuleType;
    typedef ftKineticMediatorImpl MediatorType;
};

// Same with a fighter specific mediator (ftKineticMediatorImplT<ftXxxKineticTransactor>).
template <typename T, typename M>
class soKineticModuleBuildConfigMediator {
public:
    typedef T ModuleType;
    typedef M MediatorType;
};

template <typename BC>
class soKineticModuleBuilder {
    typename BC::ModuleType m_module;     // +0x0
    ftKineticEnergyManager m_manager;     // +0x30
    typename BC::MediatorType m_mediator; // +0xE0
public:
    soKineticModuleBuilder(soModuleAccesser* acc) :
        m_module(acc, &m_manager, &m_mediator), m_manager(false), m_mediator(acc) { }
    soKineticModule* getModule() { return &m_module; }
};
