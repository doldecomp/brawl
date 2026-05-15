#include <StaticAssert.h>
#include <ft/ft_entry.h>
#include <so/so_module_accesser.h>
#include <sr/sr_common.h>
#include <types.h>

class soModuleAccesserBuildData {
public:

};

class ftFighterBuildData : public soModuleAccesserBuildData {
public:
    ftFighterBuildData(s32 entryId, ftKind kind, Heaps::HeapType instHeap,
                       Heaps::HeapType nwModelInstHeap,
                       Heaps::HeapType nwMotionInstHeap,
                       s8 resGroupNo, soModuleAccesser* acc,
                       s32 team, void* cameraRangeSet,
                       void* cameraClipSphereSet);
};
