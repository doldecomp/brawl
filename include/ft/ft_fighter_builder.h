#pragma once

// Shared fighter module builder scaffolding. Used by every ft_<char> REL.
// Each character provides a BuildConfig class (see ftPurinBuildConfig) that selects the
// module implementation types and capacities, and derives from ftFighterBuilder<BC>.

#include <so/anim/so_anim_cmd_event_presenter.h>
#include <so/situation/so_situation_event_presenter.h>
#include <so/so_heap_module_impl.h>
#include <so/status/so_status_event_presenter.h>
#include <so/so_null.h>
#include <StaticAssert.h>
#include <so/status/so_status_module_impl.h>
#include <ft/fighter.h>
#include <ft/ft_entry.h>
#include <ft/ft_extend_param_accesser.h>
#include <ft/ft_fighter_build_data.h>
#include <so/so_array.h>
#include <so/event/so_event_manage_module_impl.h>
#include <so/event/so_event_system.h>
#include <so/so_inside_event_manage_module_builder.h>
#include <so/so_instance_unit.h>
#include <so/so_module_accesser.h>
#include <so/template_utils.h>
#include <sr/sr_common.h>
#include <types.h>

#include <ft/ft_cancel_module.h>
#include <ft/ft_param_customize_module_impl.h>
#include <ft/ft_resource_id_accesser_impl.h>
#include <ft/ft_status_uniq_process_gimmick.h>
#include <ft/ft_virtual_node_matrix_pool.h>
#include <so/so_module_accesser_builder.h>
#include <ut/ut_uncopyable.h>

////////////////////////////////////////
// ftAnimCmdModuleSubBuilder
////////////////////////////////////////

template <u32 P1, u32 P2>
class ftAnimCmdModuleSubBuildConfig {
    // TODO
};


template <typename BC>
class ftAnimCmdModuleSubBuilder {
    // TODO
};


// TODO: When the Builder base classes are done, move them to separate headers

template <class BC>
class soModuleAccesserBuilder : public utUnCopyable {
public:
    soInsideEventManageModuleBuilder<typename BC::InsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> unk194;
    soModuleAccesser m_moduleAccsr; // +0x9D0 for ft_purin
    soHeapModuleBuilder<typename BC::HeapModuleBuildConfig> m_heapModuleBuilder;
    soParamCustomizeModuleBuilder<typename BC::ParamCustomizeModuleBuildConfig> m_paramCustomizeModuleBuilder;
    soResourceModuleBuilder<typename BC::ResourceModuleBuildConfig> m_resourceModuleBuilder;
    soModelModuleBuilder<typename BC::ModelModuleBuildConfig> m_modelModuleBuilder;

    // TODO: add remaining ModuleBuilders
    // Add getModule() member functions for each Builder

    u8 unkC44[0x8DF4];
    soModuleAccesserBuilder(const ftFighterBuildData& fbd) :
        m_heapModuleBuilder(fbd),
        m_paramCustomizeModuleBuilder(&m_moduleAccsr),
        m_resourceModuleBuilder(
            fbd.getMdlResId(),
            fbd.getAnmResId(),
            fbd.getResGroupNo(),
            &m_moduleAccsr
        ),
        m_modelModuleBuilder(
            &m_moduleAccsr,
            fbd.getModelExtendNodeTable(),
            &g_soEventObserverRegistrationDescNull,
            fbd.getModelScale()
        ) {
    }

    ~soModuleAccesserBuilder() { }
    soModuleAccesser* getModuleAccesser() { return &m_moduleAccsr; }
};

template <typename BC>
class ftModuleAccesserBuilder : public soModuleAccesserBuilder<BC> {
public:
    soArrayContractibleTable<const soStatusData> unkTable;
    ftAnimCmdModuleSubBuilder<typename BC::AnimCmdModuleSubBuildConfig> unkAnimCmdModuleSubBuilder;

    ftModuleAccesserBuilder(const ftFighterBuildData& fbd) : soModuleAccesserBuilder<BC>(fbd) {

    }
};

template<typename BC>
class ftFighterBuilder : public Fighter {
    ftModuleAccesserBuilder<BC> m_moduleBuilder; // +0x194
    ftCancelModuleImpl m_cancelModule;
    ftVirtualNodeMatrixPoolImpl m_virtualNodeMtxPool;
    ftStatusGimmickUniqProcessPoolImpl m_gimmickProcPool;
    u32 unk9A38[2]; // cameraRangeSet TODO type
    u32 unk9A40[2]; // cameraClipSphereSet TODO type
public:
    ftFighterBuilder(s32 entryId,
                     ftKind kind,
                     Heaps::HeapType instHeap,
                     Heaps::HeapType nwModelInstHeap,
                     Heaps::HeapType nwMotionInstHeap) :
        Fighter(entryId, kind, instHeap, &m_moduleBuilder.m_moduleAccsr),
        m_moduleBuilder(ftFighterBuildData(entryId,
                               kind,
                               instHeap,
                               nwModelInstHeap,
                               nwMotionInstHeap,
                               0,
                               m_moduleAccesser,
                               -1,
                               &unk9A38,
                               &unk9A40)),
        m_cancelModule(m_moduleAccesser),
        m_virtualNodeMtxPool(),
        m_gimmickProcPool(m_moduleAccesser) {
    }
};


