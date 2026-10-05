#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/donkey/ft_donkey.h>
#include <ft/donkey/ft_donkey_extend_param_accesser.h>

#define FT_BC ftDonkeyBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftDonkeyExtendParamAccesser g_ftDonkeyExtendParamAccesser;

ftClassInfoImpl<Fighter_Donkey, ftDonkey> g_ftClassInfoDonkey;

ftDonkey::ftDonkey(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftDonkeyBuildConfig>(entryId,
                                         Fighter_Donkey,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftDonkey is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftDonkeyInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftDonkeyInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_92_6E9C(u8* p) { return *(u8*)(p + 0x4); }
void fn_92_8C3C() {}
int fn_92_92F8() { return 0x0; }
void fn_92_947C() {}
void fn_92_95F4() {}
u8 fn_92_95F8(u8* p) { return *(u8*)(p + 0x44); }
void fn_92_9600() {}
void fn_92_9640() {}
void fn_92_9644() {}
void fn_92_96D4() {}
void fn_92_9700() {}
void fn_92_9704() {}
void fn_92_9708() {}
void fn_92_970C() {}
void fn_92_9710() {}
void fn_92_9714() {}
void fn_92_9718() {}
void fn_92_971C() {}
void fn_92_9720() {}
void fn_92_9724() {}
void fn_92_9728() {}
void fn_92_972C() {}
void fn_92_9730() {}
void fn_92_9734() {}
void fn_92_9738() {}
int fn_92_973C() { return 0x0; }
void fn_92_9744() {}
void fn_92_9748() {}
void fn_92_974C() {}
void fn_92_9750() {}
void fn_92_977C() {}
void fn_92_9780() {}
void fn_92_9784() {}
void fn_92_9788() {}
void fn_92_978C() {}
int fn_92_9790(u8* p) { return *(int*)(p + 0x110); }
int fn_92_97A8() { return 0x0; }
void fn_92_97B0() {}
void fn_92_97B4() {}
void fn_92_97B8() {}
void fn_92_97BC() {}
int fn_92_97C0() { return 0x0; }
int fn_92_97C8() { return 0x0; }
void fn_92_97D0() {}
void fn_92_97D4() {}
void fn_92_97D8() {}
void fn_92_97DC() {}
void fn_92_97E0() {}
int fn_92_9954(u8* p) { return *(int*)(p + 0x20); }
int fn_92_9A30(u8* p) { return *(int*)(p + 0x18); }
int fn_92_9AC8(u8* p) { return *(int*)(p + 0x10); }
int fn_92_9B88() { return 0x0; }
int fn_92_AB90() { return 0x2; }
void fn_92_B9D0() {}
void fn_92_C0E0() {}
int fn_92_C11C() { return 0x8; }
void fn_92_C164() {}
int fn_92_C210() { return 0x0; }
void fn_92_C24C() {}
int fn_92_C2F8() { return 0x0; }
void fn_92_C334() {}
int fn_92_C3E0() { return 0x0; }
void fn_92_C41C() {}
int fn_92_C4C8() { return 0x0; }
void fn_92_C504() {}
int fn_92_C5B0() { return 0x0; }
void fn_92_C5EC() {}
int fn_92_C698() { return 0x0; }
void fn_92_C6D4() {}
int fn_92_C780() { return 0x0; }
void fn_92_C7BC() {}
int fn_92_C868() { return 0x0; }

}
