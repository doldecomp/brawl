#pragma once

#include <StaticAssert.h>
#include <gr/gr_gimmick_motion_path.h>
#include <mt/mt_vector.h>
#include <types.h>

enum emKind {
    Enemy_Invalid = -0x1,
    Enemy_Goomba = 0x0,
    Enemy_Kuribo = 0x0,
    Enemy_Poppant = 0x1,
    Enemy_Popperam = 0x1,
    Enemy_Feyesh = 0x2,
    Enemy_Pacci = 0x2,
    Enemy_Jyk = 0x3,
    Enemy_Jyakeel = 0x3,
    Enemy_Auroros = 0x4,
    Enemy_Aroaros = 0x4,
    Enemy_Cymul = 0x5,
    Enemy_Cymal = 0x5,
    Enemy_Roturret = 0x6,
    Enemy_Deathpod = 0x6,
    Enemy_Borboras = 0x7,
    Enemy_Boobas = 0x7,
    Enemy_GiantGoomba = 0x8,
    Enemy_DekaKuribo = 0x8,
    Enemy_Buckot = 0x9,
    Enemy_Botron = 0x9,
    Enemy_Bucculus = 0xA,
    Enemy_Bucyulus = 0xA,
    Enemy_Greap = 0xB,
    Enemy_Gyraan = 0xB,
    Enemy_Armight = 0xC,
    Enemy_SirAlamos = 0xC,
    Enemy_BulletBill = 0xD,
    Enemy_Killer = 0xD,
    Enemy_Roader = 0xE,
    Enemy_Roada = 0xE,
    Enemy_Spaak = 0xF,
    Enemy_Spar = 0xF,
    Enemy_Mite = 0x10,
    Enemy_Ticken = 0x11,
    Enemy_Teckin = 0x11,
    Enemy_Towtow = 0x12,
    Enemy_Tautau = 0x12,
    Enemy_HammerBro = 0x13,
    Enemy_HammerBros = 0x13,
    Enemy_Bytan = 0x14,
    Enemy_Bitan = 0x14,
    Enemy_Floow = 0x15,
    Enemy_Flows = 0x15,
    Enemy_Puppit = 0x16,
    Enemy_Kokkon = 0x16,
    Enemy_Primid = 0x17,
    Enemy_Prim = 0x17,
    Enemy_Shellpod = 0x18,
    Enemy_Shelly = 0x18,
    Enemy_Koopa = 0x19,
    Enemy_Patapata = 0x19,
    Enemy_Shaydas = 0x1A,
    Enemy_Jdus = 0x1A,
    Enemy_Bombed = 0x1B,
    Enemy_Bombhead = 0x1B,
    Enemy_Primid_Metal = 0x1C,
    Enemy_Prim_Metal = 0x1C,
    Enemy_Nagagog = 0x1D,
    Enemy_Ngagog = 0x1D,
    Enemy_Trowlon = 0x1E,
    Enemy_Faulong = 0x1E,
    Enemy_Primid_Big = 0x1F,
    Enemy_Prim_Big = 0x1F,
    Enemy_Primid_Boom = 0x20,
    Enemy_Prim_Boomerang = 0x20,
    Enemy_Primid_Fire = 0x21,
    Enemy_Prim_Fire = 0x21,
    Enemy_Primid_Scope = 0x22,
    Enemy_Prim_SuperScope = 0x22,
    Enemy_Primid_Sword = 0x23,
    Enemy_Prim_Sword = 0x23,
    Enemy_Gamyga = 0x24,
    Enemy_Ghamgha = 0x24,
    Enemy_ROB_Blaster = 0x25,
    Enemy_Robo_Beam = 0x25,
    Enemy_ROB_Distance = 0x26,
    Enemy_Robo_Distance = 0x26,
    Enemy_ROB_Launcher = 0x27,
    Enemy_Robo_Homing = 0x27,
    Enemy_ROB_Sentry = 0x28,
    Enemy_Robo_Punch = 0x28,
    Enemy_Autolance = 0x29,
    Enemy_Cataguard = 0x29,
    Enemy_Armank = 0x2A,
    Enemy_Arman = 0x2A,
    Enemy_Glire = 0x2B,
    Enemy_Gal_Fire = 0x2B,
    Enemy_Glice = 0x2C,
    Enemy_Gal_Ice = 0x2C,
    Enemy_Glunder = 0x2D,
    Enemy_Gal_Thunder = 0x2D,
    Enemy_Boss_PeteyPiranha = 0x2E,
    Enemy_Boss_BossPackun = 0x2E,
    Enemy_GamygaBase = 0x2F,
    Enemy_Ghamghabase = 0x2F,
    Enemy_Ghamghabase_01 = 0x2F,
    Enemy_Ghamghabase_02 = 0x30,
    Enemy_Ghamghabase_03 = 0x31,
    Enemy_Ghamghabase_04 = 0x32,
    Enemy_Boss_Galleom = 0x33,
    Enemy_Boss_Ridley = 0x34,
    Enemy_Boss_Rayquaza = 0x35,
    Enemy_Boss_Duon = 0x36,
    Enemy_Boss_Porky = 0x37,
    Enemy_Boss_MetaRidley = 0x38,
    Enemy_Boss_Metaridley = 0x38,
    Enemy_Boss_FalconFlyer = 0x39,
    Enemy_Boss_Falconflyer = 0x39,
    Enemy_Boss_Tabuu = 0x3A,
    Enemy_Boss_Taboo = 0x3A,
    Enemy_Boss_MasterHand = 0x3B,
    Enemy_Boss_Masterhand = 0x3B,
    Enemy_Boss_CrazyHand = 0x3C,
    Enemy_Boss_Crazyhand = 0x3C
};
typedef emKind EnemyKind;

union i32f {
    s32 i;
    float f;
    bool b;
    u8 u8a[4];
};

// TODO: is this emValueAccesser?
struct UnkParamAccesser {
    u32 unk0;
    u8 unk4[0xBC];
    u32 unkC0;
    u8 unkC4[0x20];
    u32 unkE4;
    u8 unkE8[0x18];
    u32 unk100;
    float unk104;
    float unk108;
    float unk10C;
    u32 unk110;
    u8 unk114[0xC];
    u32 unk120;
    u32 unk124;
    u8 unk128[0x8];
    u32 unk130;
    u8 unk134[0xC];
    u32 unk140;
    s32 unk144;
    s32 unk148;
    s32 unk14C;
    float unk150;
    u32 unk154;
    u8 unk158[0xC];
    u32 unk164;
    u8 unk168[0xC];
    u32 unk174;
    u8 unk178[0x4];
    u32 unk17C;
    u32 unk180;
    u8 unk184[0x4];
    u32 unk188;
    u8 unk18C[0x8];
    u32 unk194;
    u8 unk198[0xC];
    u32 unk1A4;
    u32 unk1A8;
    u32 unk1AC;
    s32 unk1B0;
    s32 unk1B4;
    u32 unk1B8;
    u8 unk1BC[0x4];
    u32 unk1C0;
    float unk1C4;
    float unk1C8;
    u32 unk1CC;
    u32 unk1D0;
    u8 unk1D4[0x14];
    u32 unk1E8;
    u8 unk1EC[0x8];
    u32 unk1F4;
    u8 unk1F8[0x8];
    u32 unk200;
    u8 unk204[0x4];
    u32 unk208;
    u8 unk20C[0x18];
    u32 unk224;
    u8 unk228[0x4];
    u32 unk22C;
    u8 unk230[0x4];
    u32 unk234;
    u8 unk238[0x8];
    u32 unk240;
    u32 unk244;
    u32 unk248;
    u8 unk24C[0x4];
    u32 unk250;
    u32 unk254;
    u32 unk258;
    u8 unk25C[0x8];
    s32 unk264;
    s32 unk268;
    u8 unk26C[0x8];
    u32 unk274;
    float unk278;
    s32 unk27C;
    u32 unk280;
    u32 unk284;
    u32 unk288;
    float unk28C;
    float unk290;
    i32f unk294;
    float unk298;
    s32 unk29C;
    float unk2A0;
    s32 unk2A4;
    float unk2A8;
    float unk2AC;
    u32 unk2B0;
    u8 unk2B4[0xC];
    float unk2C0;
    u32 unk2C4;
    u32 unk2C8;
    u8 unk2CC[0x4];
    u32 unk2D0;
    u8 unk2D4[0x10];
    u32 unk2E4;
    u32 unk2E8;
    u8 unk2EC;
    s32 unk2F0;
    float unk2F4;
    float unk2F8;
    u32 unk2FC;
    u32 unk300;
    s32 unk304;
    s32 unk308;
    float unk30C;
    float unk310;
    float unk314;
    float unk318;
    float unk31C;
    float unk320;
    float unk324;
    float unk328;
    i32f unk32C;
    i32f unk330;
    float unk334;
    float unk338;
    float unk33C;
    i32f unk340;
    i32f unk344;
    float unk348;
    i32f unk34C;
    float unk350;
    float unk354;
    float unk358;
    s32 unk35C;
    s32 unk360;
    s32 unk364;
    i32f unk368;
    i32f unk36C;
    i32f unk370;
    s32 unk374;
    float unk378;
    i32f unk37C;
    float unk380;
    u32 unk384;
    float unk388;
    float unk38C;
    float unk390;
    float unk394;
    i32f unk398;
    u32 unk39C;
    u32 unk3A0;
    u8 unk3A4[0x4];
    u32 unk3A8;
    u8 unk3AC[0x4];
    s32 unk3B0;
    s32 unk3B4;
    s32 unk3B8;
    float unk3BC;
    float unk3C0;
    float unk3C4;
    u32 unk3C8;
    u32 unk3CC;
    u32 unk3D0;
    u8 unk3D4[0x4];
    u32 unk3D8;
    u8 unk3DC[0x8];
    u32 unk3E4;
    u32 unk3E8;
    u8 unk3EC[0x4];
    u32 unk3F0;
    u8 unk3F4[0x4];
    u32 unk3F8;
    u32 unk3FC;
    u32 unk400;
    s32 unk404;
    s32 unk408;
    float unk40C;
    float unk410;
    float unk414;
    float unk418;
    u32 unk41C;
    u8 unk420[0x4];
    u32 unk424;
    u32 unk428;
    u32 unk42C;
    u8 unk430[0x4];
    s32 unk434;
    s32 unk438;
    u32 unk43C;
    u32 unk440;
    u32 unk444;
    u8 unk448[0x4];
    u32 unk44C;
    u32 unk450;
    u8 unk454[0x4];
    u32 unk458;
    u32 unk45C;
    u8 unk460[0x4];
    u32 unk464;
    u32 unk468;
    u8 unk46C[0x4];
    u32 unk470;
    u32 unk474;
    u8 unk478[0x4];
    u32 unk47C;
    u32 unk480;
    u8 unk484[0x4];
    s32 unk488;
    s32 unk48C;
    s32 unk490;
    s32 unk494;
    u32 unk498;
    u32 unk49C;
    float unk4A0;
    float unk4A4;
    float unk4A8;
    float unk4AC;
    u8 unk4B0[0x4];
    u32 unk4B4;
    u8 unk4B8[0x4];
    u32 unk4BC;
    u32 unk4C0;
    i32f unk4C4;
    i32f unk4C8;
    i32f unk4CC;
    float unk4D0;
    float unk4D4;
    float unk4D8;
    s32 unk4DC;
    u32 unk4E0;
    u8 unk4E4[0x4];
    u32 unk4E8;
    u32 unk4EC;
    u32 unk4F0;
    u32 unk4F4;
    u32 unk4F8;
    u8 unk4FC;
    s32 unk500;
    s32 unk504;
    u32 unk508;
    s32 unk50C;
    float unk510;
    u32 unk514;
    u32 unk518;
    u32 unk51C;
    u32 unk520;
    u32 unk524;
    u8 unk528[0x4];
    s32 unk52C;
    u8 unk530[0x4];
    u32 unk534;
    u8 unk538[0x4];
    float unk53C;
    s32 unk540;
    float unk544;
    float unk548;
    float unk54C;
    u32 unk550;
    u8 unk554[0x18];
    u32 unk56C;
    u8 unk570[0x4];
    u32 unk574;
    u32 unk578;
    u8 unk57C[0x4];
    u32 unk580;
    u32 unk584;
    u32 unk588;
    u8 unk58C[0x4];
    u32 unk590;
    u32 unk594;
    u8 unk598[0x4];
    u32 unk59C;
    u8 unk5A0[0x8];
    u32 unk5A8;
    u32 unk5AC;
    u8 unk5B0[0x4];
    s32 unk5B4;
    s32 unk5B8;
    s32 unk5BC;
    s32 unk5C0;
    s32 unk5C4;
    i32f unk5C8;
    i32f unk5CC;
    s32 unk5D0;
    s32 unk5D4;
    float unk5D8;
    float unk5DC;
    float unk5E0;
    float unk5E4;
    float unk5E8;
    float unk5EC;
    float unk5F0;
    u32 unk5F4;
    u8 unk5F8[0x4];
    u32 unk5FC;
    u32 unk600;
    u8 unk604[0x8];
    s32 unk60C;
    s32 unk610;
    s32 unk614;
    s32 unk618;
    float unk61C;
    float unk620;
    float unk624;
    float unk628;
    float unk62C;
    u32 unk630;
    u32 unk634;
    u32 unk638;
    u32 unk63C;
    u32 unk640;
    u32 unk644;
    u32 unk648;
    s32 unk64C;
    u8 unk650;
    u32 unk654;
    u8 unk658[0x4];
    s32 unk65C;
    s32 unk660;
    u32 unk664;
    u32 unk668;
    u32 unk66C;
    u32 unk670;
    u32 unk674;
    u32 unk678;
    u8 unk67C[0x4];
    u32 unk680;
    u32 unk684;
    u32 unk688;
    u32 unk68C;
    u32 unk690;
    float unk694;
    float unk698;
    float unk69C;
    u32 unk6A0;
    u8 unk6A4[0x4];
    u32 unk6A8;
    u32 unk6AC;
    float unk6B0;
    float unk6B4;
    u32 unk6B8;
    u8 unk6BC[0x4];
    u32 unk6C0;
    u32 unk6C4;
    u8 unk6C8[0x4];
    u32 unk6CC;
    u8 unk6D0[0x8];
    u32 unk6D8;
    u8 unk6DC[0x4];
    u32 unk6E0;
    u32 unk6E4;
    u32 unk6E8;
    u8 unk6EC[0x4];
    u32 unk6F0;
    u8 unk6F4[0x8];
    u32 unk6FC;
    u32 unk700;
    u8 unk704[0x4];
    u32 unk708;
    u8 unk70C[0x4];
    u32 unk710;
    u32 unk714;
    u32 unk718;
    u8 unk71C[0x4];
    u32 unk720;
    u8 unk724[0x4];
    u32 unk728;
    u32 unk72C;
    u8 unk730[0x8];
    u32 unk738;
    u8 unk73C;
    u32 unk740;
    u32 unk744;
    u8 unk748[0x8];
    u32 unk750;
    u8 unk754[0x8];
    u32 unk75C;
    u8 unk760[0x8];
    u32 unk768;
    u8 unk76C[0x8];
    u32 unk774;
    u8 unk778[0x8];
    u32 unk780;
    u32 unk784;
    u32 unk788;
    u32 unk78C;
    u8 unk790[0x4];
    u32 unk794;
    u32 unk798;
    u8 unk79C[0x8];
    u32 unk7A4;
    u8 unk7A8[0x8];
    u32 unk7B0;
    u8 unk7B4[0x8];
    u32 unk7BC;
    u8 unk7C0[0x8];
    u32 unk7C8;
    u8 unk7CC[0x4];
    u32 unk7D0;
    u32 unk7D4;
    u8 unk7D8[0x8];
    s32 unk7E0;
    float unk7E4;
    u32 unk7E8;
    u32 unk7EC;
    u8 unk7F0[0x8];
    u32 unk7F8;
    u32 unk7FC;
    u8 unk800[0x4];
    u32 unk804;
    u32 unk808;
    u8 unk80C[0x4];
    u32 unk810;
    u8 unk814[0x4];
    float unk818;
    u32 unk81C;
    u8 unk820;
    u32 unk824;
    u32 unk828;
    u8 unk82C[0x8];
    s32 unk834;
    s32 unk838;
    u32 unk83C;
    u8 unk840[0x4];
    s32 unk844;
    s32 unk848;
    s32 unk84C;
    s32 unk850;
    u32 unk854;
    u8 unk858[0x4];
    u32 unk85C;
    u32 unk860;
    u8 unk864[0x40];
    u32 unk8A4;
    u8 unk8A8[0x18];
    float unk8C0;
    u8 unk8C4[0x8];
    u32 unk8CC;
    u8 unk8D0[0x8];
    u32 unk8D8;
    u32 unk8DC;
    u8 unk8E0[0x20];
    u32 unk900;
    u8 unk904[0x8];
    u32 unk90C;
    u8 unk910[0x10];
    u32 unk920;
    u8 unk924[0x18];
    u32 unk93C;
    u8 unk940[0x8];
    u32 unk948;
    u8 unk94C[0x8];
    u32 unk954;
    u8 unk958[0x14];
    u32 unk96C;
    u8 unk970[0x8];
    u32 unk978;
    u8 unk97C[0x4];
    u32 unk980;
    u8 unk984[0x18];
    u32 unk99C;
    u8 unk9A0[0x4];
    u32 unk9A4;
    u8 unk9A8[0x1C];
    float unk9C4;
    float unk9C8;
    float unk9CC;
    float unk9D0;
    s32 unk9D4;
    s32 unk9D8;
    float unk9DC;
    i32f unk9E0;
    float unk9E4;
    float unk9E8;
    float unk9EC;
    float unk9F0;
    float unk9F4;
    float unk9F8;
    float unk9FC;
    float unkA00;
    float unkA04;
    float unkA08;
    float unkA0C;
    u32 unkA10;
    u8 unkA14[0x8];
    u32 unkA1C;
    u8 unkA20[0x8];
    u32 unkA28;
    u8 unkA2C[0x4];
    u32 unkA30;
    u32 unkA34;
    u32 unkA38;
    u8 unkA3C[0x4];
    float unkA40;
    float unkA44;
    float unkA48;
    s32 unkA4C;
    u8 unkA50[0x14];
    u32 unkA64;
    u8 unkA68[0x8];
    u32 unkA70;
    u8 unkA74[0x2C];
    u32 unkAA0;
    u8 unkAA4[0x2C];
    u32 unkAD0;
    u8 unkAD4[0x20];
    u32 unkAF4;
    u8 unkAF8[0x8];
    u32 unkB00;
    u8 unkB04[0x20];
    u32 unkB24;
    u8 unkB28[0x20];
    u32 unkB48;
    u8 unkB4C[0x8];
    u32 unkB54;
    u8 unkB58[0x30];
    s32 unkB88;
    s32 unkB8C;
    s32 unkB90;
    s32 unkB94;
    s32 unkB98;
    s32 unkB9C;
    s32 unkBA0;
    float unkBA4;
    float unkBA8;
    float unkBAC;
    float unkBB0;
    float unkBB4;
    float unkBB8;
    float unkBBC;
    float unkBC0;
    float unkBC4;
    float unkBC8;
    float unkBCC;
    float unkBD0;
    float unkBD4;
    float unkBD8;
    u32 unkBDC;
    u8 unkBE0[0xC];
    u32 unkBEC;
    u8 unkBF0[0x8];
    u32 unkBF8;
    u8 unkBFC[0x8];
    u32 unkC04;
    u8 unkC08[0x8];
    u32 unkC10;
    u8 unkC14[0x8];
    u32 unkC1C;
    u8 unkC20[0x20];
    u32 unkC40;
    u8 unkC44[0x20];
    u32 unkC64;
    u8 unkC68[0x20];
    u32 unkC88;
    u8 unkC8C[0x20];
    u32 unkCAC;
    u8 unkCB0[0x14];
    u32 unkCC4;
    u8 unkCC8[0xB8];
    u32 unkD80;
    u8 unkD84[0x188];
    u32 unkF0C;
    u8 unkF10[0x17C];
    u32 unk108C;
    u8 unk1090[0x20];
    u32 unk10B0;
    u8 unk10B4[0xC];
    u32 unk10C0;
    u8 unk10C4[0x38];
    u32 unk10FC;
    u8 unk1100[0x44];
    u32 unk1144;
    u8 unk1148[0x38];
    u32 unk1180;
    u8 unk1184[0x38];
    u32 unk11BC;
    u8 unk11C0[0x44];
    u32 unk1204;
    u8 unk1208[0x38];
    u32 unk1240;
    u8 unk1244[0x14];
    u32 unk1258;
    u8 unk125C[0x14];
    u32 unk1270;
    u8 unk1274[0x14];
    u32 unk1288;
    u8 unk128C[0x14];
    u32 unk12A0;
    u8 unk12A4[0x14];
    u32 unk12B8;
    u8 unk12BC[0x14];
    u32 unk12D0;
    u8 unk12D4[0x14];
    u32 unk12E8;
    u8 unk12EC[0x14];
    u32 unk1300;
    u8 unk1304[0x14];
    u32 unk1318;
    u8 unk131C[0x14];
    float unk1330;
    float unk1334;
    float unk1338;
    float unk133C;
    float unk1340;
    s32 unk1344;
    u32 unk1348;
    u8 unk134C[0x4];
    u32 unk1350;
    u8 unk1354[0x4];
    float unk1358;
    float unk135C;
    float unk1360;
    u32 unk1364;
    u8 unk1368[0xC];
    u32 unk1374;
    u8 unk1378[0x4];
    u32 unk137C;
    u8 unk1380[0xC];
    u32 unk138C;
    u8 unk1390[0xC];
    u32 unk139C;
    u8 unk13A0[0xC];
    float unk13AC;
    u32 unk13B0;
    u8 unk13B4[0x78];
    u32 unk142C;
    u8 unk1430[0x78];
    u32 unk14A8;
    u8 unk14AC[0x78];
    u32 unk1524;
    u8 unk1528[0x78];
    u32 unk15A0;
    u8 unk15A4[0x24];
    u32 unk15C8;
};

class emCreate {
public:
    u8 m_difficulty;
    EnemyKind m_enemyKind;
    int m_teamNo;
    float m_startLr;
    Vec3f m_startPos;
    u32 m_startStatusKind;
    u8 m_level;
    float m_36;
    Rect2D m_territoryRange;
    int m_connectedTriggerId;
    void* m_epbm;
    UnkParamAccesser* m_epsp;
    grGimmickMotionPath* m_motionPath;
    int m_parentCreateId;

    emCreate();
    virtual ~emCreate();
};
static_assert(sizeof(emCreate) == 80, "Class is wrong size!");
