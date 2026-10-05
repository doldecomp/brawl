#include <ft/builder/ft_dol_array_list.h>
#include <ft/ft_class_info_impl.h>
#include <ft/iceclimber/ft_iceclimber.h>
#include <ft/iceclimber/ft_iceclimber_extend_param_accesser.h>

#define FT_BC ftPopoBuildConfig
#include <ft/builder/ft_builder_noinline.h>

ftPopoExtendParamAccesser g_ftPopoExtendParamAccesser;

ftClassInfoImpl<Fighter_Popo, ftPopo> g_ftClassInfoPopo;

ftPopo::ftPopo(s32 entryId,
                 Heaps::HeapType instHeap,
                 Heaps::HeapType nwModelInstHeap,
                 Heaps::HeapType nwMotionInstHeap) :
    ftFighterBuilder<ftPopoBuildConfig>(entryId,
                                         Fighter_Popo,
                                         instHeap,
                                         nwModelInstHeap,
                                         nwMotionInstHeap) {
    // TODO
}

// FIXME: Test code present only to emit the shared builder functions; delete once ftPopo is done
void testBuilder() {
    soInsideEventManageModuleBuilder<ftPopoInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> insideBuilder;
    soResourceIdAccesserImpl idAccImpl(0, 1, 2);
}
soInsideEventManageModuleBuilder<ftPopoInsideEventManageModuleBuildConfig, ftInsideEventManageModuleTypes> g_insideBuilder;

// Trivial functions of this translation unit (empty virtuals, constant returns, field accessors) under their placeholder names.
extern "C" {

u8 fn_105_8130(u8* p) { return *(u8*)(p + 0x4); }
void fn_105_A0DC() {}
void fn_105_AAFC() {}
void fn_105_AB14() {}
void fn_105_AB2C() {}
void fn_105_AB44() {}
void fn_105_AF48() {}
u8 fn_105_AF4C(u8* p) { return *(u8*)(p + 0x44); }
void fn_105_BF14() {}
int fn_105_D540() { return 0x0; }
void fn_105_D76C() {}
void fn_105_D8E4() {}
void fn_105_D924() {}
void fn_105_D928() {}
void fn_105_D9E0() {}
void fn_105_D9E4() {}
void fn_105_D9E8() {}
void fn_105_D9EC() {}
void fn_105_D9F0() {}
void fn_105_D9F4() {}
void fn_105_D9F8() {}
void fn_105_D9FC() {}
void fn_105_DA00() {}
void fn_105_DA04() {}
void fn_105_DA08() {}
void fn_105_DA0C() {}
void fn_105_DA10() {}
void fn_105_DA14() {}
void fn_105_DA18() {}
int fn_105_DA1C() { return 0x0; }
void fn_105_DA24() {}
void fn_105_DA28() {}
void fn_105_DA2C() {}
void fn_105_DA30() {}
void fn_105_DA5C() {}
void fn_105_DA60() {}
void fn_105_DA64() {}
void fn_105_DA68() {}
void fn_105_DA6C() {}
int fn_105_DA70(u8* p) { return *(int*)(p + 0x110); }
int fn_105_DA88() { return 0x0; }
void fn_105_DA90() {}
void fn_105_DA94() {}
void fn_105_DA98() {}
int fn_105_DA9C() { return 0x0; }
int fn_105_DAA4() { return 0x0; }
void fn_105_DAAC() {}
void fn_105_DAB0() {}
void fn_105_DAB4() {}
void fn_105_DAB8() {}
void fn_105_DABC() {}
void fn_105_DAC0() {}
void fn_105_DAC4() {}
void fn_105_DAC8() {}
void fn_105_DACC() {}
void fn_105_DAD0() {}
int fn_105_DAD4() { return -0x1; }
int fn_105_DAEC(u8* p) { return *(int*)(p + 0xc); }
int fn_105_DAF4() { return 0x0; }
void fn_105_DAFC() {}
void fn_105_DB00(u8* p, int v) { *(int*)(p + 0xc) = v; }
int fn_105_DC18(u8* p) { return *(int*)(p + 0x20); }
int fn_105_DCF4(u8* p) { return *(int*)(p + 0x18); }
int fn_105_DD8C(u8* p) { return *(int*)(p + 0x10); }
int fn_105_DE4C() { return 0x0; }
int fn_105_F458() { return 0x5; }
void fn_105_1038C() {}
void fn_105_10D70() {}
int fn_105_10DAC() { return 0x8; }
int fn_105_11194() { return 0x0; }
int fn_105_11564() { return 0x0; }
int fn_105_11930() { return 0x0; }
int fn_105_11CF4() { return 0x0; }
int fn_105_120D0() { return 0x0; }
int fn_105_124AC() { return 0x0; }
int fn_105_12888() { return 0x0; }
int fn_105_12C64() { return 0x0; }

}
