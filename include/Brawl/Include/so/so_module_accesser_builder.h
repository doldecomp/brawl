#pragma once

#include <ft/ft_fighter_build_data.h>
#include <so/event/so_event_presenter.h>
#include <so/model/so_model_virtual_node.h>
#include <so/resource/so_resource_module_impl.h>
#include <types.h>

class soModuleAccesser;

////////////////////////////////////////
// soHeapModuleBuilder
////////////////////////////////////////

template <typename T>
class soHeapModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soHeapModuleBuilder {
    typename BC::ModuleType m_heapModule;
public:
    soHeapModuleBuilder(const ftFighterBuildData& fbd) :
        m_heapModule(
            fbd.getInstanceHeap(),
            fbd.getNWModelInstanceHeap(),
            fbd.getNWMotionInstanceHeap(),
            fbd.getHeapSlotNo()
        ) { }
};

////////////////////////////////////////
// soParamCustomizeModuleBuilder
////////////////////////////////////////

template <typename T>
class soParamCustomizeModuleBuildConfig {
public:
    typedef T ModuleType;
};

template <typename BC>
class soParamCustomizeModuleBuilder {
    typename BC::ModuleType m_paramCustomizeModule;
public:
    soParamCustomizeModuleBuilder(soModuleAccesser* accsr) :
        m_paramCustomizeModule(accsr) { }
};

////////////////////////////////////////
// soResourceModuleBuilder
////////////////////////////////////////

template <u32 M, typename I, typename T>
class soResourceModuleBuildConfig {
public:
    enum { ManagerId = M };
    typedef I IdAccesserType;
    typedef T ModuleType;
};

template <u32 M, typename I, typename T>
class soResourceModuleBuildConfigDynamic {
public:
    enum { ManagerId = M };
    typedef I IdAccesserType;
    typedef T ModuleType;
};

class soResourceModuleBuildConfigNull { };

template <typename BC>
class soResourceModuleBuilder {
    typename BC::IdAccesserType m_idAccsr;
    typename BC::ModuleType m_resourceModule;
public:
    static typename BC::ModuleType* getModule(soResourceModuleBuilder* b) {
        return &b->m_resourceModule;
    }

    soResourceModuleBuilder(u32 mdlResId, u32 anmResId, u8 resGrpNo, soModuleAccesser* accsr) :
        m_idAccsr(accsr), m_resourceModule(BC::ManagerId, &m_idAccsr, resGrpNo) { }
};

template <u32 M, typename I, typename T>
class soResourceModuleBuilder<soResourceModuleBuildConfig<M, I, T> > {
    I m_idAccsr;
    T m_resourceModule;
public:
    static T* getModule(soResourceModuleBuilder* b) {
        return &b->m_resourceModule;
    }

    soResourceModuleBuilder(u32 mdlResId, u32 anmResId, u8 resGrpNo, soModuleAccesser* accsr) :
        m_idAccsr(mdlResId, mdlResId, anmResId), m_resourceModule(M, &m_idAccsr, resGrpNo) { }
};

template <>
class soResourceModuleBuilder<soResourceModuleBuildConfigNull> {
public:
    soResourceModuleBuilder(u32 mdlResId, u32 anmResId, u8 resGrpNo, soModuleAccesser* accsr) { }

    static soResourceModule* getModule(soResourceModuleBuilder* b) {
        return &g_soResourceModuleNull;
    }
};

////////////////////////////////////////
// soModelModuleBuilder
////////////////////////////////////////

template <u32 S, u32 N, typename T>
class soModelModuleBuildConfig {
public:
    enum {
        NodeSetUpCap = S,
        VirtualNodeCap = N,
    };
    typedef T ModuleType;
};

template <typename BC>
class soModelModuleBuilder {
    soArrayVector<soModelNodeSetUp, BC::NodeSetUpCap> m_nodeSetUps;
    soArrayVector<soModelVirtualNode, BC::VirtualNodeCap> m_virtualNodes;
    typename BC::ModuleType m_modelModule;
public:
    static typename BC::ModuleType* getModule(soModelModuleBuilder* b) {
        return &b->m_modelModule;
    }

    soModelModuleBuilder(soModuleAccesser* acc,
                         void* extendNodeTbl,
                         soEventObserverRegistrationDesc* regDesc,
                         float modelScale) :
        m_nodeSetUps(BC::NodeSetUpCap),
        m_virtualNodes(BC::VirtualNodeCap),
        m_modelModule(
            acc,
            &m_nodeSetUps,
            extendNodeTbl,
            &m_virtualNodes,
            regDesc,
            modelScale
        ) {
    }
};

template <u32 S, typename T>
class soModelModuleBuilder<soModelModuleBuildConfig<S, 0, T> > {
    soArrayVector<soModelNodeSetUp, S> m_nodeSetUps;
    soArrayVector<soModelVirtualNode, 0> m_virtualNodes;
    T m_modelModule;
public:
    static T* getModule(soModelModuleBuilder* b) {
        return &b->m_modelModule;
    }

    soModelModuleBuilder(soModuleAccesser* acc,
                         void* extendNodeTable,
                         soEventObserverRegistrationDesc* regDesc,
                         float modelScale) :
        m_nodeSetUps(S),
        m_virtualNodes(),
        m_modelModule(
            acc,
            &m_nodeSetUps,
            extendNodeTable,
            &getNullArray<soModelVirtualNode>(),
            regDesc,
            modelScale
        ) {
    }
};
