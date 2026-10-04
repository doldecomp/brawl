#include <ft/builder/ft_dol_array_list.h>
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
#include <ft/purin/ft_purin_extend_param_accesser.h>
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

#include <ft/ft_fighter_builder.h>

////////////////////////////////////////
// Jigglypuff Build Configuration
////////////////////////////////////////

typedef soInsideEventManageModuleBuildConfig<
    32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes
> ftPurinInsideEventManageModuleBuildConfig;
typedef soHeapModuleBuildConfig<soHeapModuleImpl> ftPurinHeapModuleBuildConfig;
typedef soParamCustomizeModuleBuildConfig<ftParamCustomizeModuleImpl> ftPurinParamCustomizeModuleBuildConfig;
typedef soResourceModuleBuildConfigDynamic<0, ftResourceIdAccesserImpl, soResourceModuleImpl> ftPurinResourceModuleBuildConfig;
typedef soModelModuleBuildConfig<8, 3, soModelModuleImpl> ftPurinModelModuleBuildConfig;

typedef ftAnimCmdModuleSubBuildConfig<288, 501> ftPurinAnimCmdModuleSubBuildConfig;

class ftPurinBuildConfig : public ftCommonBuildConfig {
public:
    typedef ftPurinInsideEventManageModuleBuildConfig InsideEventManageModuleBuildConfig;
    typedef ftPurinHeapModuleBuildConfig HeapModuleBuildConfig;
    typedef ftPurinParamCustomizeModuleBuildConfig ParamCustomizeModuleBuildConfig;
    typedef ftPurinResourceModuleBuildConfig ResourceModuleBuildConfig;
    typedef ftPurinAnimCmdModuleSubBuildConfig AnimCmdModuleSubBuildConfig;
    typedef ftPurinModelModuleBuildConfig ModelModuleBuildConfig;
};

class ftPurin : public ftFighterBuilder<ftPurinBuildConfig> {

    // begin ftPurin fields
    soArrayContractibleTable<const soStatusData> unk9A48;
    void* unk9A58; // TODO type
public:
    ftPurin(s32 entryId,
            Heaps::HeapType instHeap,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
// static_assert(sizeof(ftPurin) == 0x9A5C, "Class is the wrong size!");

#define FT_BC ftPurinBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftPurin::ftPurin(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftPurinBuildConfig>(entryId,
                                         Fighter_Jigglypuff,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the constructor; delete once ftPurin is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftPurinInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
    ftPopoResourceIdAccesserImpl popoIdAccImpl(nullptr);
}
soInsideEventManageModuleBuilder<ftPurinInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

ftPurinExtendParamAccesser g_ftPurinExtendParamAccesser;
