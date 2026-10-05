#pragma once

#include <StaticAssert.h>
#include <ft/ft_entry.h>
#include <ft/ft_extend_param_accesser.h>
#include <types.h>

// TODO: identify the special moves the ExtendParam groups are for
// TODO: Match without the const_cast hack (the Cast accessors load the group pointer again)
// TODO: UBFIX endianness

class ftKirbyExtendParamAccesser : public ftExtendParamAccesserEx<3999, 291, 23999, 78> {
    const u8* group1(const u8* base) { return *(const u8* const*)(base + 0x7C); }
    const u8* group1Cast(const u8* base) { return *(const u8**)(base + 0x7C); }
    const u8* group2(const u8* base) { return *(const u8* const*)(base + 0x80); }
    const u8* group2Cast(const u8* base) { return *(const u8**)(base + 0x80); }
    const u8* group3(const u8* base) { return *(const u8* const*)(base + 0x84); }
    const u8* group3Cast(const u8* base) { return *(const u8**)(base + 0x84); }
    const u8* group4(const u8* base) { return *(const u8* const*)(base + 0x88); }
    const u8* group4Cast(const u8* base) { return *(const u8**)(base + 0x88); }
    const u8* group5(const u8* base) { return *(const u8* const*)(base + 0x8C); }
    const u8* group5Cast(const u8* base) { return *(const u8**)(base + 0x8C); }
    const u8* group6(const u8* base) { return *(const u8* const*)(base + 0x90); }
    const u8* group6Cast(const u8* base) { return *(const u8**)(base + 0x90); }
    const u8* group7(const u8* base) { return *(const u8* const*)(base + 0x94); }
    const u8* group7Cast(const u8* base) { return *(const u8**)(base + 0x94); }
    const u8* group8(const u8* base) { return *(const u8* const*)(base + 0x98); }
    const u8* group8Cast(const u8* base) { return *(const u8**)(base + 0x98); }
    const u8* group9(const u8* base) { return *(const u8* const*)(base + 0x9C); }
    const u8* group9Cast(const u8* base) { return *(const u8**)(base + 0x9C); }
    const u8* group10(const u8* base) { return *(const u8* const*)(base + 0xA0); }
    const u8* group10Cast(const u8* base) { return *(const u8**)(base + 0xA0); }
    const u8* group11(const u8* base) { return *(const u8* const*)(base + 0xA4); }
    const u8* group11Cast(const u8* base) { return *(const u8**)(base + 0xA4); }
    const u8* group12(const u8* base) { return *(const u8* const*)(base + 0xA8); }
    const u8* group12Cast(const u8* base) { return *(const u8**)(base + 0xA8); }
    const u8* group13(const u8* base) { return *(const u8* const*)(base + 0xAC); }
    const u8* group13Cast(const u8* base) { return *(const u8**)(base + 0xAC); }
    const u8* group14(const u8* base) { return *(const u8* const*)(base + 0xB0); }
    const u8* group14Cast(const u8* base) { return *(const u8**)(base + 0xB0); }
    const u8* group15(const u8* base) { return *(const u8* const*)(base + 0xB4); }
    const u8* group15Cast(const u8* base) { return *(const u8**)(base + 0xB4); }
    const u8* group16(const u8* base) { return *(const u8* const*)(base + 0xB8); }
    const u8* group16Cast(const u8* base) { return *(const u8**)(base + 0xB8); }
    const u8* group17(const u8* base) { return *(const u8* const*)(base + 0xBC); }
    const u8* group17Cast(const u8* base) { return *(const u8**)(base + 0xBC); }
    const u8* group18(const u8* base) { return *(const u8* const*)(base + 0xC0); }
    const u8* group18Cast(const u8* base) { return *(const u8**)(base + 0xC0); }
    const u8* group19(const u8* base) { return *(const u8* const*)(base + 0xC4); }
    const u8* group19Cast(const u8* base) { return *(const u8**)(base + 0xC4); }
    const u8* group20(const u8* base) { return *(const u8* const*)(base + 0xC8); }
    const u8* group20Cast(const u8* base) { return *(const u8**)(base + 0xC8); }
    const u8* group21(const u8* base) { return *(const u8* const*)(base + 0xCC); }
    const u8* group21Cast(const u8* base) { return *(const u8**)(base + 0xCC); }
    const u8* group22(const u8* base) { return *(const u8* const*)(base + 0xD0); }
    const u8* group22Cast(const u8* base) { return *(const u8**)(base + 0xD0); }
    const u8* group23(const u8* base) { return *(const u8* const*)(base + 0xD4); }
    const u8* group23Cast(const u8* base) { return *(const u8**)(base + 0xD4); }
    const u8* group24(const u8* base) { return *(const u8* const*)(base + 0xD8); }
    const u8* group24Cast(const u8* base) { return *(const u8**)(base + 0xD8); }
    const u8* group25(const u8* base) { return *(const u8* const*)(base + 0xDC); }
    const u8* group25Cast(const u8* base) { return *(const u8**)(base + 0xDC); }
    const u8* group26(const u8* base) { return *(const u8* const*)(base + 0xE0); }
    const u8* group26Cast(const u8* base) { return *(const u8**)(base + 0xE0); }
    const u8* group27(const u8* base) { return *(const u8* const*)(base + 0xE4); }
    const u8* group27Cast(const u8* base) { return *(const u8**)(base + 0xE4); }
    const u8* group28(const u8* base) { return *(const u8* const*)(base + 0xE8); }
    const u8* group28Cast(const u8* base) { return *(const u8**)(base + 0xE8); }
    const u8* group29(const u8* base) { return *(const u8* const*)(base + 0xEC); }
    const u8* group29Cast(const u8* base) { return *(const u8**)(base + 0xEC); }
    const u8* group30(const u8* base) { return *(const u8* const*)(base + 0xF0); }
    const u8* group30Cast(const u8* base) { return *(const u8**)(base + 0xF0); }
    const u8* group31(const u8* base) { return *(const u8* const*)(base + 0xF4); }
    const u8* group31Cast(const u8* base) { return *(const u8**)(base + 0xF4); }
    const u8* group32(const u8* base) { return *(const u8* const*)(base + 0xF8); }
    const u8* group32Cast(const u8* base) { return *(const u8**)(base + 0xF8); }
    const u8* group33(const u8* base) { return *(const u8* const*)(base + 0xFC); }
    const u8* group33Cast(const u8* base) { return *(const u8**)(base + 0xFC); }
    const u8* group34(const u8* base) { return *(const u8* const*)(base + 0x100); }
    const u8* group34Cast(const u8* base) { return *(const u8**)(base + 0x100); }
    const u8* group35(const u8* base) { return *(const u8* const*)(base + 0x104); }
    const u8* group35Cast(const u8* base) { return *(const u8**)(base + 0x104); }
    const u8* group36(const u8* base) { return *(const u8* const*)(base + 0x108); }
    const u8* group36Cast(const u8* base) { return *(const u8**)(base + 0x108); }
    const u8* group37(const u8* base) { return *(const u8* const*)(base + 0x10C); }
    const u8* group37Cast(const u8* base) { return *(const u8**)(base + 0x10C); }
    const u8* group38(const u8* base) { return *(const u8* const*)(base + 0x110); }
    const u8* group38Cast(const u8* base) { return *(const u8**)(base + 0x110); }
    const u8* group39(const u8* base) { return *(const u8* const*)(base + 0x114); }
    const u8* group39Cast(const u8* base) { return *(const u8**)(base + 0x114); }
    const u8* group40(const u8* base) { return *(const u8* const*)(base + 0x118); }
    const u8* group40Cast(const u8* base) { return *(const u8**)(base + 0x118); }
    const u8* group41(const u8* base) { return *(const u8* const*)(base + 0x11C); }
    const u8* group41Cast(const u8* base) { return *(const u8**)(base + 0x11C); }

public:
    ftKirbyExtendParamAccesser() : ftExtendParamAccesserEx(Fighter_Kirby) { }
    virtual ~ftKirbyExtendParamAccesser() { }

    virtual void setup(const u8* extData) {
        for (s32 i = 0; i < NumVariations; i++) {
            m_floats[i][0] = (const float*)(group1(extData) + 0x4);
            m_floats[i][1] = (const float*)(group1(extData) + 0x8);
            m_floats[i][2] = (const float*)(group1(extData) + 0xC);
            m_floats[i][3] = (const float*)(group1(extData) + 0x10);
            m_floats[i][4] = (const float*)(group1(extData) + 0x14);
            m_floats[i][5] = (const float*)(group1(extData) + 0x18);
            m_floats[i][6] = (const float*)(group1(extData) + 0x1C);
            m_floats[i][7] = (const float*)(group1(extData) + 0x20);
            m_floats[i][8] = (const float*)(group1(extData) + 0x24);
            m_floats[i][9] = (const float*)(group1(extData) + 0x28);
            m_floats[i][10] = (const float*)(group1(extData) + 0x30);
            m_floats[i][11] = (const float*)(group1(extData) + 0x34);
            m_floats[i][12] = (const float*)(group2Cast(extData) + 0x0);
            m_floats[i][13] = (const float*)(group3Cast(extData) + 0x0);
            m_floats[i][14] = (const float*)(group3(extData) + 0x4);
            m_floats[i][15] = (const float*)(group3(extData) + 0x8);
            m_floats[i][16] = (const float*)(group3(extData) + 0xC);
            m_floats[i][17] = (const float*)(group3(extData) + 0x10);
            m_floats[i][18] = (const float*)(group3(extData) + 0x14);
            m_floats[i][19] = (const float*)(group4(extData) + 0x8);
            m_floats[i][20] = (const float*)(group4(extData) + 0xC);
            m_floats[i][21] = (const float*)(group4(extData) + 0x10);
            m_floats[i][22] = (const float*)(group4(extData) + 0x14);
            m_floats[i][23] = (const float*)(group4(extData) + 0x18);
            m_floats[i][24] = (const float*)(group4(extData) + 0x1C);
            m_floats[i][25] = (const float*)(group4(extData) + 0x20);
            m_floats[i][26] = (const float*)(group4(extData) + 0x24);
            m_floats[i][27] = (const float*)(group4(extData) + 0x28);
            m_floats[i][28] = (const float*)(group5(extData) + 0x1C);
            m_floats[i][29] = (const float*)(group5(extData) + 0x28);
            m_floats[i][30] = (const float*)(group5(extData) + 0x2C);
            m_floats[i][31] = (const float*)(group5(extData) + 0x30);
            m_floats[i][32] = (const float*)(group5(extData) + 0x34);
            m_floats[i][33] = (const float*)(group5(extData) + 0x4C);
            m_floats[i][34] = (const float*)(group5(extData) + 0x50);
            m_floats[i][35] = (const float*)(group5(extData) + 0x54);
            m_floats[i][36] = (const float*)(group5(extData) + 0x58);
            m_floats[i][37] = (const float*)(group5(extData) + 0x5C);
            m_floats[i][38] = (const float*)(group5(extData) + 0x64);
            m_floats[i][39] = (const float*)(group6Cast(extData) + 0x0);
            m_floats[i][40] = (const float*)(group6(extData) + 0x4);
            m_floats[i][41] = (const float*)(group6(extData) + 0x8);
            m_floats[i][42] = (const float*)(group6(extData) + 0xC);
            m_floats[i][43] = (const float*)(group6(extData) + 0x10);
            m_floats[i][44] = (const float*)(group7Cast(extData) + 0x0);
            m_floats[i][45] = (const float*)(group7(extData) + 0x4);
            m_floats[i][46] = (const float*)(group7(extData) + 0x8);
            m_floats[i][47] = (const float*)(group7(extData) + 0xC);
            m_floats[i][48] = (const float*)(group8Cast(extData) + 0x0);
            m_floats[i][49] = (const float*)(group8(extData) + 0x4);
            m_floats[i][50] = (const float*)(group8(extData) + 0x8);
            m_floats[i][51] = (const float*)(group8(extData) + 0xC);
            m_floats[i][52] = (const float*)(group8(extData) + 0x10);
            m_floats[i][53] = (const float*)(group8(extData) + 0x14);
            m_floats[i][54] = (const float*)(group8(extData) + 0x18);
            m_floats[i][55] = (const float*)(group8(extData) + 0x1C);
            m_floats[i][56] = (const float*)(group8(extData) + 0x20);
            m_floats[i][57] = (const float*)(group8(extData) + 0x24);
            m_floats[i][58] = (const float*)(group8(extData) + 0x28);
            m_floats[i][59] = (const float*)(group8(extData) + 0x30);
            m_floats[i][60] = (const float*)(group8(extData) + 0x34);
            m_floats[i][61] = (const float*)(group8(extData) + 0x38);
            m_floats[i][62] = (const float*)(group8(extData) + 0x3C);
            m_floats[i][63] = (const float*)(group8(extData) + 0x44);
            m_floats[i][64] = (const float*)(group8(extData) + 0x48);
            m_floats[i][72] = (const float*)(group9Cast(extData) + 0x0);
            m_floats[i][73] = (const float*)(group9(extData) + 0x4);
            m_floats[i][74] = (const float*)(group9(extData) + 0x8);
            m_floats[i][75] = (const float*)(group9(extData) + 0x14);
            m_floats[i][76] = (const float*)(group9(extData) + 0x18);
            m_floats[i][77] = (const float*)(group9(extData) + 0x1C);
            m_floats[i][78] = (const float*)(group9(extData) + 0x20);
            m_floats[i][79] = (const float*)(group9(extData) + 0x24);
            m_floats[i][80] = (const float*)(group9(extData) + 0x28);
            m_floats[i][81] = (const float*)(group9(extData) + 0x30);
            m_floats[i][82] = (const float*)(group9(extData) + 0x34);
            m_floats[i][83] = (const float*)(group9(extData) + 0x38);
            m_floats[i][84] = (const float*)(group9(extData) + 0x3C);
            m_floats[i][85] = (const float*)(group9(extData) + 0x40);
            m_floats[i][86] = (const float*)(group9(extData) + 0x44);
            m_floats[i][87] = (const float*)(group9(extData) + 0x4C);
            m_floats[i][88] = (const float*)(group9(extData) + 0x50);
            m_floats[i][89] = (const float*)(group9(extData) + 0x58);
            m_floats[i][90] = (const float*)(group10Cast(extData) + 0x0);
            m_floats[i][91] = (const float*)(group10(extData) + 0x4);
            m_floats[i][92] = (const float*)(group10(extData) + 0x8);
            m_floats[i][93] = (const float*)(group10(extData) + 0xC);
            m_floats[i][94] = (const float*)(group10(extData) + 0x10);
            m_floats[i][95] = (const float*)(group10(extData) + 0x14);
            m_floats[i][96] = (const float*)(group11Cast(extData) + 0x0);
            m_floats[i][97] = (const float*)(group11(extData) + 0x4);
            m_floats[i][98] = (const float*)(group11(extData) + 0x8);
            m_floats[i][99] = (const float*)(group11(extData) + 0xC);
            m_floats[i][100] = (const float*)(group11(extData) + 0x10);
            m_floats[i][101] = (const float*)(group11(extData) + 0x14);
            m_floats[i][102] = (const float*)(group12Cast(extData) + 0x0);
            m_floats[i][103] = (const float*)(group12(extData) + 0x4);
            m_floats[i][104] = (const float*)(group12(extData) + 0x8);
            m_floats[i][105] = (const float*)(group12(extData) + 0xC);
            m_floats[i][106] = (const float*)(group12(extData) + 0x10);
            m_floats[i][107] = (const float*)(group12(extData) + 0x14);
            m_floats[i][108] = (const float*)(group13Cast(extData) + 0x0);
            m_floats[i][109] = (const float*)(group13(extData) + 0x4);
            m_floats[i][110] = (const float*)(group13(extData) + 0x8);
            m_floats[i][111] = (const float*)(group13(extData) + 0xC);
            m_floats[i][112] = (const float*)(group13(extData) + 0x10);
            m_floats[i][113] = (const float*)(group13(extData) + 0x14);
            m_floats[i][114] = (const float*)(group13(extData) + 0x1C);
            m_floats[i][115] = (const float*)(group13(extData) + 0x20);
            m_floats[i][116] = (const float*)(group13(extData) + 0x24);
            m_floats[i][117] = (const float*)(group13(extData) + 0x28);
            m_floats[i][118] = (const float*)(group13(extData) + 0x2C);
            m_floats[i][119] = (const float*)(group13(extData) + 0x30);
            m_floats[i][120] = (const float*)(group13(extData) + 0x34);
            m_floats[i][121] = (const float*)(group13(extData) + 0x38);
            m_floats[i][122] = (const float*)(group13(extData) + 0x44);
            m_floats[i][123] = (const float*)(group13(extData) + 0x48);
            m_floats[i][124] = (const float*)(group13(extData) + 0x4C);
            m_floats[i][125] = (const float*)(group14(extData) + 0x4);
            m_floats[i][126] = (const float*)(group14(extData) + 0x8);
            m_floats[i][127] = (const float*)(group15(extData) + 0x4);
            m_floats[i][128] = (const float*)(group15(extData) + 0x8);
            m_floats[i][129] = (const float*)(group15(extData) + 0xC);
            m_floats[i][130] = (const float*)(group15(extData) + 0x10);
            m_floats[i][131] = (const float*)(group15(extData) + 0x14);
            m_floats[i][132] = (const float*)(group15(extData) + 0x18);
            m_floats[i][133] = (const float*)(group15(extData) + 0x20);
            m_floats[i][65] = (const float*)(group16(extData) + 0x8);
            m_floats[i][66] = (const float*)(group16(extData) + 0xC);
            m_floats[i][67] = (const float*)(group16(extData) + 0x10);
            m_floats[i][68] = (const float*)(group16(extData) + 0x14);
            m_floats[i][69] = (const float*)(group16(extData) + 0x18);
            m_floats[i][70] = (const float*)(group16(extData) + 0x1C);
            m_floats[i][71] = (const float*)(group16(extData) + 0x20);
            m_floats[i][134] = (const float*)(group17Cast(extData) + 0x0);
            m_floats[i][135] = (const float*)(group17(extData) + 0x4);
            m_floats[i][136] = (const float*)(group17(extData) + 0x8);
            m_floats[i][137] = (const float*)(group17(extData) + 0xC);
            m_floats[i][138] = (const float*)(group17(extData) + 0x10);
            m_floats[i][139] = (const float*)(group18Cast(extData) + 0x0);
            m_floats[i][140] = (const float*)(group18(extData) + 0x4);
            m_floats[i][141] = (const float*)(group18(extData) + 0x8);
            m_floats[i][142] = (const float*)(group18(extData) + 0xC);
            m_floats[i][143] = (const float*)(group19Cast(extData) + 0x0);
            m_floats[i][144] = (const float*)(group19(extData) + 0x4);
            m_floats[i][145] = (const float*)(group19(extData) + 0x8);
            m_floats[i][146] = (const float*)(group19(extData) + 0xC);
            m_floats[i][147] = (const float*)(group19(extData) + 0x10);
            m_floats[i][148] = (const float*)(group19(extData) + 0x14);
            m_floats[i][149] = (const float*)(group19(extData) + 0x18);
            m_floats[i][150] = (const float*)(group19(extData) + 0x1C);
            m_floats[i][151] = (const float*)(group19(extData) + 0x20);
            m_floats[i][152] = (const float*)(group20Cast(extData) + 0x0);
            m_floats[i][-2] = (const float*)(group20Cast(extData) + 0x0);
            m_floats[i][153] = (const float*)(group19(extData) + 0x8);
            m_floats[i][154] = (const float*)(group19(extData) + 0xC);
            m_floats[i][155] = (const float*)(group21Cast(extData) + 0x0);
            m_floats[i][156] = (const float*)(group21(extData) + 0x4);
            m_floats[i][157] = (const float*)(group21(extData) + 0x8);
            m_floats[i][158] = (const float*)(group21(extData) + 0xC);
            m_floats[i][159] = (const float*)(group21(extData) + 0x10);
            m_floats[i][160] = (const float*)(group22(extData) + 0xC);
            m_floats[i][161] = (const float*)(group22(extData) + 0x10);
            m_floats[i][162] = (const float*)(group23(extData) + 0xC);
            m_floats[i][163] = (const float*)(group23(extData) + 0x10);
            m_floats[i][-1] = (const float*)(group24Cast(extData) + 0x0);
            m_floats[i][164] = (const float*)(group21(extData) + 0x8);
            m_floats[i][165] = (const float*)(group21(extData) + 0xC);
            m_floats[i][166] = (const float*)(group25(extData) + 0xC);
            m_floats[i][167] = (const float*)(group25(extData) + 0x10);
            m_floats[i][168] = (const float*)(group25(extData) + 0x14);
            m_floats[i][3] = (const float*)(group26Cast(extData) + 0x0);
            m_floats[i][169] = (const float*)(group21(extData) + 0xC);
            m_floats[i][170] = (const float*)(group21(extData) + 0x10);
            m_floats[i][171] = (const float*)(group27(extData) + 0x8);
            m_floats[i][172] = (const float*)(group27(extData) + 0xC);
            m_floats[i][173] = (const float*)(group27(extData) + 0x10);
            m_floats[i][174] = (const float*)(group27(extData) + 0x14);
            m_floats[i][175] = (const float*)(group27(extData) + 0x18);
            m_floats[i][176] = (const float*)(group27(extData) + 0x1C);
            m_floats[i][177] = (const float*)(group27(extData) + 0x20);
            m_floats[i][178] = (const float*)(group27(extData) + 0x24);
            m_floats[i][179] = (const float*)(group27(extData) + 0x28);
            m_floats[i][180] = (const float*)(group27(extData) + 0x2C);
            m_floats[i][181] = (const float*)(group27(extData) + 0x30);
            m_floats[i][182] = (const float*)(group27(extData) + 0x34);
            m_floats[i][183] = (const float*)(group27(extData) + 0x38);
            m_floats[i][184] = (const float*)(group27(extData) + 0x40);
            m_floats[i][185] = (const float*)(group27(extData) + 0x44);
            m_floats[i][186] = (const float*)(group27(extData) + 0x48);
            m_floats[i][187] = (const float*)(group27(extData) + 0x4C);
            m_floats[i][188] = (const float*)(group27(extData) + 0x50);
            m_floats[i][189] = (const float*)(group27(extData) + 0x54);
            m_floats[i][190] = (const float*)(group27(extData) + 0x58);
            m_floats[i][191] = (const float*)(group27(extData) + 0x5C);
            m_floats[i][192] = (const float*)(group27(extData) + 0x60);
            m_floats[i][193] = (const float*)(group27(extData) + 0x64);
            m_floats[i][194] = (const float*)(group27(extData) + 0x6C);
            m_floats[i][195] = (const float*)(group27(extData) + 0x70);
            m_floats[i][196] = (const float*)(group27(extData) + 0x74);
            m_floats[i][197] = (const float*)(group27(extData) + 0x78);
            m_floats[i][198] = (const float*)(group27(extData) + 0x7C);
            m_floats[i][199] = (const float*)(group27(extData) + 0x80);
            m_floats[i][200] = (const float*)(group27(extData) + 0x84);
            m_floats[i][201] = (const float*)(group27(extData) + 0x88);
            m_floats[i][202] = (const float*)(group27(extData) + 0x8C);
            m_floats[i][203] = (const float*)(group27(extData) + 0x90);
            m_floats[i][204] = (const float*)(group27(extData) + 0x94);
            m_floats[i][205] = (const float*)(group27(extData) + 0x98);
            m_floats[i][206] = (const float*)(group27(extData) + 0x9C);
            m_floats[i][207] = (const float*)(group27(extData) + 0xA0);
            m_floats[i][208] = (const float*)(group27(extData) + 0xA4);
            m_floats[i][209] = (const float*)(group28Cast(extData) + 0x0);
            m_floats[i][210] = (const float*)(group28(extData) + 0x4);
            m_floats[i][211] = (const float*)(group28(extData) + 0x8);
            m_floats[i][212] = (const float*)(group28(extData) + 0xC);
            m_floats[i][213] = (const float*)(group28(extData) + 0x10);
            m_floats[i][214] = (const float*)(group28(extData) + 0x14);
            m_floats[i][215] = (const float*)(group28(extData) + 0x18);
            m_floats[i][216] = (const float*)(group28(extData) + 0x20);
            m_floats[i][217] = (const float*)(group28(extData) + 0x24);
            m_floats[i][218] = (const float*)(group29Cast(extData) + 0x0);
            m_floats[i][219] = (const float*)(group29(extData) + 0x4);
            m_floats[i][220] = (const float*)(group29(extData) + 0x8);
            m_floats[i][221] = (const float*)(group29(extData) + 0xC);
            m_floats[i][222] = (const float*)(group29(extData) + 0x10);
            m_floats[i][223] = (const float*)(group29(extData) + 0x14);
            m_floats[i][224] = (const float*)(group29(extData) + 0x18);
            m_floats[i][225] = (const float*)(group29(extData) + 0x1C);
            m_floats[i][226] = (const float*)(group29(extData) + 0x20);
            m_floats[i][227] = (const float*)(group29(extData) + 0x24);
            m_floats[i][228] = (const float*)(group29(extData) + 0x28);
            m_floats[i][229] = (const float*)(group29(extData) + 0x34);
            m_floats[i][230] = (const float*)(group29(extData) + 0x38);
            m_floats[i][231] = (const float*)(group29(extData) + 0x3C);
            m_floats[i][232] = (const float*)(group30(extData) + 0x4);
            m_floats[i][233] = (const float*)(group30(extData) + 0x8);
            m_floats[i][234] = (const float*)(group30(extData) + 0xC);
            m_floats[i][235] = (const float*)(group30(extData) + 0x10);
            m_floats[i][236] = (const float*)(group30(extData) + 0x14);
            m_floats[i][237] = (const float*)(group30(extData) + 0x18);
            m_floats[i][238] = (const float*)(group30(extData) + 0x1C);
            m_floats[i][239] = (const float*)(group30(extData) + 0x24);
            m_floats[i][240] = (const float*)(group30(extData) + 0x28);
            m_floats[i][241] = (const float*)(group30(extData) + 0x2C);
            m_floats[i][242] = (const float*)(group31Cast(extData) + 0x0);
            m_floats[i][243] = (const float*)(group31(extData) + 0x4);
            m_floats[i][244] = (const float*)(group32(extData) + 0x4);
            m_floats[i][245] = (const float*)(group32(extData) + 0x8);
            m_floats[i][246] = (const float*)(group33Cast(extData) + 0x0);
            m_floats[i][247] = (const float*)(group33(extData) + 0x4);
            m_floats[i][248] = (const float*)(group33(extData) + 0x8);
            m_floats[i][249] = (const float*)(group33(extData) + 0xC);
            m_floats[i][250] = (const float*)(group33(extData) + 0x10);
            m_floats[i][251] = (const float*)(group34Cast(extData) + 0x0);
            m_floats[i][252] = (const float*)(group34(extData) + 0x4);
            m_floats[i][253] = (const float*)(group34(extData) + 0x8);
            m_floats[i][254] = (const float*)(group34(extData) + 0xC);
            m_floats[i][255] = (const float*)(group35Cast(extData) + 0x0);
            m_floats[i][256] = (const float*)(group35(extData) + 0x4);
            m_floats[i][257] = (const float*)(group35(extData) + 0x8);
            m_floats[i][258] = (const float*)(group35(extData) + 0xC);
            m_floats[i][259] = (const float*)(group36(extData) + 0x4);
            m_floats[i][260] = (const float*)(group36(extData) + 0x8);
            m_floats[i][261] = (const float*)(group36(extData) + 0xC);
            m_floats[i][262] = (const float*)(group36(extData) + 0x14);
            m_floats[i][263] = (const float*)(group36(extData) + 0x18);
            m_floats[i][264] = (const float*)(group36(extData) + 0x1C);
            m_floats[i][265] = (const float*)(group37(extData) + 0x4);
            m_floats[i][266] = (const float*)(group37(extData) + 0x8);
            m_floats[i][267] = (const float*)(group37(extData) + 0xC);
            m_floats[i][268] = (const float*)(group38Cast(extData) + 0x0);
            m_floats[i][269] = (const float*)(group38(extData) + 0x4);
            m_floats[i][270] = (const float*)(group38(extData) + 0x8);
            m_floats[i][271] = (const float*)(group38(extData) + 0xC);
            m_floats[i][272] = (const float*)(group38(extData) + 0x10);
            m_floats[i][273] = (const float*)(group38(extData) + 0x14);
            m_floats[i][274] = (const float*)(group38(extData) + 0x1C);
            m_floats[i][275] = (const float*)(group38(extData) + 0x20);
            m_floats[i][276] = (const float*)(group38(extData) + 0x24);
            m_floats[i][277] = (const float*)(group38(extData) + 0x28);
            m_floats[i][278] = (const float*)(group38(extData) + 0x2C);
            m_floats[i][279] = (const float*)(group38(extData) + 0x30);
            m_floats[i][280] = (const float*)(group38(extData) + 0x34);
            m_floats[i][281] = (const float*)(group38(extData) + 0x38);
            m_floats[i][282] = (const float*)(group38(extData) + 0x44);
            m_floats[i][283] = (const float*)(group38(extData) + 0x48);
            m_floats[i][284] = (const float*)(group38(extData) + 0x4C);
            m_floats[i][285] = (const float*)(group39Cast(extData) + 0x0);
            m_floats[i][0] = (const float*)(group39Cast(extData) + 0x0);
            m_floats[i][286] = (const float*)(group39Cast(extData) + 0x0);
            m_floats[i][287] = (const float*)(group39Cast(extData) + 0x0);
            m_floats[i][288] = (const float*)(group40Cast(extData) + 0x0);
            m_floats[i][289] = (const float*)(group41Cast(extData) + 0x0);
            m_floats[i][1] = (const float*)(group41Cast(extData) + 0x0);
            m_floats[i][290] = (const float*)(group41Cast(extData) + 0x0);
            m_floats[i][2] = (const float*)(group1Cast(extData) + 0x0);
            m_ints[i][0] = (const int*)(group1Cast(extData) + 0x0);
            m_ints[i][1] = (const int*)(group1(extData) + 0x2C);
            m_ints[i][2] = (const int*)(group2(extData) + 0x4);
            m_ints[i][3] = (const int*)(group2(extData) + 0x8);
            m_ints[i][4] = (const int*)(group4Cast(extData) + 0x0);
            m_ints[i][5] = (const int*)(group4(extData) + 0x4);
            m_ints[i][6] = (const int*)(group5Cast(extData) + 0x0);
            m_ints[i][7] = (const int*)(group5(extData) + 0x4);
            m_ints[i][8] = (const int*)(group5(extData) + 0x8);
            m_ints[i][9] = (const int*)(group5(extData) + 0xC);
            m_ints[i][10] = (const int*)(group5(extData) + 0x10);
            m_ints[i][11] = (const int*)(group5(extData) + 0x14);
            m_ints[i][12] = (const int*)(group5(extData) + 0x18);
            m_ints[i][13] = (const int*)(group5(extData) + 0x20);
            m_ints[i][14] = (const int*)(group5(extData) + 0x24);
            m_ints[i][15] = (const int*)(group5(extData) + 0x38);
            m_ints[i][16] = (const int*)(group5(extData) + 0x3C);
            m_ints[i][17] = (const int*)(group5(extData) + 0x40);
            m_ints[i][18] = (const int*)(group5(extData) + 0x44);
            m_ints[i][19] = (const int*)(group5(extData) + 0x48);
            m_ints[i][20] = (const int*)(group5(extData) + 0x60);
            m_ints[i][21] = (const int*)(group7(extData) + 0x10);
            m_ints[i][22] = (const int*)(group8(extData) + 0x2C);
            m_ints[i][23] = (const int*)(group8(extData) + 0x40);
            m_ints[i][27] = (const int*)(group9(extData) + 0xC);
            m_ints[i][28] = (const int*)(group9(extData) + 0x10);
            m_ints[i][29] = (const int*)(group9(extData) + 0x2C);
            m_ints[i][30] = (const int*)(group9(extData) + 0x48);
            m_ints[i][31] = (const int*)(group9(extData) + 0x54);
            m_ints[i][32] = (const int*)(group9(extData) + 0x5C);
            m_ints[i][33] = (const int*)(group10(extData) + 0x18);
            m_ints[i][34] = (const int*)(group11(extData) + 0x18);
            m_ints[i][35] = (const int*)(group12(extData) + 0x18);
            m_ints[i][36] = (const int*)(group13(extData) + 0x18);
            m_ints[i][37] = (const int*)(group13(extData) + 0x3C);
            m_ints[i][38] = (const int*)(group13(extData) + 0x40);
            m_ints[i][39] = (const int*)(group14Cast(extData) + 0x0);
            m_ints[i][40] = (const int*)(group14(extData) + 0xC);
            m_ints[i][41] = (const int*)(group14(extData) + 0x10);
            m_ints[i][42] = (const int*)(group15Cast(extData) + 0x0);
            m_ints[i][43] = (const int*)(group15(extData) + 0x1C);
            m_ints[i][24] = (const int*)(group16Cast(extData) + 0x0);
            m_ints[i][25] = (const int*)(group16(extData) + 0x4);
            m_ints[i][26] = (const int*)(group16(extData) + 0x24);
            m_ints[i][44] = (const int*)(group17(extData) + 0x14);
            m_ints[i][45] = (const int*)(group2(extData) + 0x4);
            m_ints[i][46] = (const int*)(group22Cast(extData) + 0x0);
            m_ints[i][47] = (const int*)(group22(extData) + 0x4);
            m_ints[i][48] = (const int*)(group22(extData) + 0x8);
            m_ints[i][49] = (const int*)(group23Cast(extData) + 0x0);
            m_ints[i][50] = (const int*)(group23(extData) + 0x4);
            m_ints[i][51] = (const int*)(group23(extData) + 0x8);
            m_ints[i][52] = (const int*)(group24Cast(extData) + 0x0);
            m_ints[i][53] = (const int*)(group22(extData) + 0x4);
            m_ints[i][54] = (const int*)(group25Cast(extData) + 0x0);
            m_ints[i][55] = (const int*)(group25(extData) + 0x4);
            m_ints[i][56] = (const int*)(group25(extData) + 0x8);
            m_ints[i][57] = (const int*)(group26Cast(extData) + 0x0);
            m_ints[i][58] = (const int*)(group25(extData) + 0x4);
            m_ints[i][59] = (const int*)(group25(extData) + 0x8);
            m_ints[i][60] = (const int*)(group27Cast(extData) + 0x0);
            m_ints[i][61] = (const int*)(group27(extData) + 0x4);
            m_ints[i][62] = (const int*)(group27(extData) + 0x3C);
            m_ints[i][63] = (const int*)(group27(extData) + 0x68);
            m_ints[i][64] = (const int*)(group28(extData) + 0x1C);
            m_ints[i][65] = (const int*)(group29(extData) + 0x2C);
            m_ints[i][66] = (const int*)(group29(extData) + 0x30);
            m_ints[i][67] = (const int*)(group30Cast(extData) + 0x0);
            m_ints[i][68] = (const int*)(group30(extData) + 0x20);
            m_ints[i][69] = (const int*)(group32Cast(extData) + 0x0);
            m_ints[i][70] = (const int*)(group36Cast(extData) + 0x0);
            m_ints[i][71] = (const int*)(group36(extData) + 0x10);
            m_ints[i][72] = (const int*)(group37Cast(extData) + 0x0);
            m_ints[i][73] = (const int*)(group38(extData) + 0x18);
            m_ints[i][74] = (const int*)(group38(extData) + 0x3C);
            m_ints[i][75] = (const int*)(group38(extData) + 0x40);
            m_ints[i][76] = (const int*)(group38(extData) + 0x4);
            m_ints[i][77] = (const int*)(group40(extData) + 0x4);
        }
    }
};

extern ftKirbyExtendParamAccesser g_ftKirbyExtendParamAccesser;
