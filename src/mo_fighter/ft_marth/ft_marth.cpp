#include <ft/ft_class_info_impl.h>
#include <ft/marth/ft_marth.h>
#include <ft/marth/ft_marth_extend_param_accesser.h>

ftMarthExtendParamAccesser g_ftMarthExtendParamAccesser;

ftClassInfoImpl<Fighter_Marth, ftMarth> g_ftClassInfoMarth;

ftMarth::ftMarth(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftMarthBuildConfig>(entryId,
                                         Fighter_Marth,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
}
