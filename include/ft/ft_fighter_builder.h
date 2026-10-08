#pragma once
#include <ft/builder/ft_dol_array_list.h>

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
#include <ft/builder/ft_module_builders.h>
#include <ut/ut_uncopyable.h>

////////////////////////////////////////
// ftAnimCmdModuleSubBuilder
////////////////////////////////////////

// ftAnimCmdModuleSubBuildConfig / ftAnimCmdModuleSubBuilder: see ft/builder/ft_builder_animcmd.h


#include <ft/builder/ft_module_accesser_builder.h>

template<typename BC>
class ftFighterBuilder : public Fighter {
    ftModuleAccesserBuilder<BC> m_moduleBuilder; // +0x194
    ftCancelModuleImpl m_cancelModule;
    ftVirtualNodeMatrixPoolImpl m_virtualNodeMtxPool;
    ftStatusGimmickUniqProcessPoolImpl m_gimmickProcPool;
    soSet<soCameraRange> m_cameraRangeSet;
    soSet<soCameraClipSphere> m_cameraClipSphereSet;
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
                               &m_cameraRangeSet,
                               &m_cameraClipSphereSet),
                           this),
        m_cancelModule(m_moduleAccesser),
        m_virtualNodeMtxPool(),
        m_gimmickProcPool(((void)0, m_moduleAccesser)), // MATCH-ONLY: keeps the module accesser in the original saved register
        m_cameraRangeSet(static_cast<soCameraRange*>(soValueAccesser::getConstantIndefinite(m_moduleAccesser, 0xA7F9, 0)), 1),
        m_cameraClipSphereSet(static_cast<soCameraClipSphere*>(soValueAccesser::getConstantIndefinite(m_moduleAccesser, 0xA7FC, 0)), 1) {
        // Modules now own their backing storage, camera sets and gimmick processes.
        Fighter::postInitialize();
        static_cast<ftCancelModule&>(m_cancelModule).postInitialize(m_moduleAccesser);
    }
    virtual void* getCancelModule() { return &m_cancelModule; }
    virtual bool isEnableCancel() {
        return static_cast<ftCancelModule*>(&m_cancelModule)->isEnableCancel();
    }
    virtual void* getVirtualNodeMatrixPool() { return &m_virtualNodeMtxPool; }
    virtual void* getStatusGimmickUniqProcessPool() { return &m_gimmickProcPool; }
};


