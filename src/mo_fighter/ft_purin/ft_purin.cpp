#include <ft/ft_entry.h>
#include <ft/ft_extend_param_accesser.h>
#include <ft/purin/ft_purin_extend_param_accesser.h>
#include <so/so_array.h>
#include <so/so_module_accesser.h>
#include <sr/sr_common.h>
#include <StaticAssert.h>
#include <ft/fighter.h>
#include <types.h>

ftPurinExtendParamAccesser g_ftPurinExtendParamAccesser;

template<typename BuildConfig>
class ftFighterBuilder : public Fighter {
public:
    ftFighterBuilder(s32 entryId, ftKind kind, s32 p3, soModuleAccesser* acc) :
        Fighter(entryId, kind, p3, acc) {
        // TODO create ftFighterBuildData

    }
};

// TODO: Are there more template params?
template<u32 C1, u32 C2, u32 C3, u32 C4, u32 C5,
         u32 C6, u32 C7, u32 C8, u32 C9, u32 C10,
         u32 C11, u32 C12, u32 C13, u32 C14, u32 C15,
         u32 C16, u32 C17, u32 C18>
class soInsideEventManageModuleBuildConfig {

};
// size is 0x9A48

// e.g. soEventUnitWithWorkArea<soStatusEventObserver,32>
// TODO: more template params?
template<typename Cfg>
class soInsideEventManageModuleBuilder {
public:
    soInsideEventManageModuleBuilder();
};

class ftPurinBuildConfig {

};

// Note: The values passed here are the capacities of
// the soEventUnitWithWorkAreas managed by the builder
typedef soInsideEventManageModuleBuildConfig
    <32, 40, 4, 4, 4, 4, 4, 4, 5, 4, 4, 4, 4, 4, 1, 1, 2, 1>
ftPurinInsideEventManageModuleBuildConfig;

class ftPurin : public ftFighterBuilder<ftPurinBuildConfig> {
    soInsideEventManageModuleBuilder<ftPurinInsideEventManageModuleBuildConfig> unk194;
    u8 unk198[0x9CC];
    soModuleAccesser unkB64;
    u8 unkC44[0x8DF4];
    u32 unk9A38; // cameraRangeSet TODO type
    u8 unk9A3C[0x4];
    u32 unk9A40; // cameraClipSphereSet TODO type

    // begin ftPurin fields
    soArrayContractibleTable<const soStatusData> unk9A48;
    void* unk9A58; // TODO type
public:
    ftPurin(s32 entryId,
            s32 p2,
            Heaps::HeapType nwModelInstHeap,
            Heaps::HeapType nwMotionInstHeap);
};
// static_assert(sizeof(ftPurin) == 0x9A5C, "Class is the wrong size!");

ftPurin::ftPurin(s32 entryId,
                 s32 p2,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftPurinBuildConfig>(entryId, Fighter_Jigglypuff, p2, &unkB64) {
    // TODO
}
