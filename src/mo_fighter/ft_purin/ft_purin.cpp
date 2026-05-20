#include <StaticAssert.h>
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

typedef soInsideEventManageModuleBuildConfig
    <32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 0, 2, 1, ftInsideEventManageModuleTypes>
ftPurinInsideEventManageModuleBuildConfig;

// FIXME: Present only to emit the constructor; delete once ftPurin is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftPurinInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
}
soInsideEventManageModuleBuilder<ftPurinInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

ftPurinExtendParamAccesser g_ftPurinExtendParamAccesser;

template<typename BC>
class ftFighterBuilder : public Fighter {
    BC m_buildConfig; // +0x194
    u32 unk9A38[2]; // cameraRangeSet TODO type
    u32 unk9A40[2]; // cameraClipSphereSet TODO type

public:
    ftFighterBuilder(s32 entryId,
                     ftKind kind,
                     Heaps::HeapType instHeap,
                     Heaps::HeapType nwModelInstHeap,
                     Heaps::HeapType nwMotionInstHeap) :
        Fighter(entryId, kind, instHeap, &m_buildConfig.unkB64),
        m_buildConfig(ftFighterBuildData(entryId,
                               Fighter_Jigglypuff,
                               instHeap,
                               nwModelInstHeap,
                               nwMotionInstHeap,
                               0,
                               m_moduleAccesser,
                               -1,
                               &unk9A38,
                               &unk9A40)) {
    }
};

class ftPurinBuildConfig {
public:
    soInsideEventManageModuleBuilder<ftPurinInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> unk194;
    soModuleAccesser unkB64;
    u8 unkC44[0x8DF4];
    ftPurinBuildConfig(const ftFighterBuildData& fbd) {

    }
    ~ftPurinBuildConfig() { }
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
