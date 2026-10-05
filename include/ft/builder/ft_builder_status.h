#pragma once

// soStatusModuleBuilder<soStatusModuleBuildConfig<StatusKinds, GeneralWork, 274, 71, Transition>> (0xEB8 bytes):
// ftMarth fn_106_6224 (ctor) / fn_106_3394 (dtor); the soStatusModuleImpl is at +0xE08.
//   soStatusModuleBuilder(soModuleAccesser*, fbd.getStatusData(), fbd.getPreCheckAnimCmdData())

#include <ft/builder/ft_builder_general_work.h>
#include <ft/builder/ft_builder_transition.h>
#include <ft/builder/ft_dol_types.h>
#include <so/status/so_status_module_impl.h>
#include <types.h>

// HYPOTHESIS: unk274 is the status data count, unk71 is unknown.
template <s32 StatusKinds, typename GeneralWorkConfig, s32 StatusDataCount, s32 Unk71, typename TransitionConfig>
class soStatusModuleBuildConfig {
public:
    enum { StatusKindCap = StatusKinds, DataCount = StatusDataCount, Unk = Unk71 };
    typedef GeneralWorkConfig GeneralWorkBuildConfig;
    typedef TransitionConfig TransitionBuildConfig;
};

template <s32 I, typename V, typename Null>
class soArraySelectHolder {
public:
    V m_array;
    soArraySelectHolder() : m_array(0) { }
    soArraySelectHolder(s32 size, s32 unk) : m_array(size, unk) { }
    ~soArraySelectHolder() { }
    V* get() { return &m_array; }
};

template <typename V>
class soArrayQueueImpl {
    V* m_array;
    V m_vector;
public:
    soArrayQueueImpl(const s32& initial) : m_array(&m_vector), m_vector(1, initial, 0) {
        soArray<s32>* array = &m_vector;
        array->capacity();
    }
};

template <typename BC>
class soStatusModuleBuilder {
    soArrayContractibleTable<const soStatusData> m_statusTable;                                           // +0x0
    soGeneralWorkBuilder<typename BC::GeneralWorkBuildConfig> m_generalWorkBuilder;                       // +0x10
    soTransitionModuleBuilder<typename BC::TransitionBuildConfig> m_transitionBuilder;                    // +0xF0
    soArraySelectHolder<1, soArrayVector<soStatusUniqProcess*, BC::StatusKindCap>, soArrayNull<soStatusUniqProcess*> > m_uniqProcs; // +0x964
    soArrayQueueImpl<soArrayVector<s32, 1> > m_changeRequests;                                            // +0xDF4
    soStatusModuleImpl m_module;                                                                          // +0xE08
    u32 unkEB4;
public:
    soStatusModuleBuilder(soModuleAccesser* acc, const soStatusData* statusData, void* preCheckData) :
        m_statusTable(statusData, BC::DataCount),
        m_generalWorkBuilder(),
        m_transitionBuilder(),
        m_uniqProcs(),
        m_changeRequests(-1),
        m_module(acc, &m_statusTable, (soArray<soStatusUniqProcess*>*)m_uniqProcs.get(), m_generalWorkBuilder.getModule(),
                 m_transitionBuilder.getModule(), &m_changeRequests, preCheckData, BC::StatusKindCap, 1) { }
    soStatusModule* getModule() { return &m_module; }
};
