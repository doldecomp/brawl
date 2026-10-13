#pragma once

#include <types.h>

namespace Heaps {
    enum HeapType {
        SystemFW = 0x1,
        System = 0x2,
        Effect = 0x3,
        RenderFifo = 0x4,
        Sound = 0x5,
        Network = 0x6,
        WiiPad = 0x7,
        IteamResource = 0x8,
        ItemResource = 0x8,
        InfoResource = 0x9,
        CommonResource = 0xa,
        Replay = 0xb,
        Tmp = 0xc,
        Physics = 0xd,
        ItemInstance = 0xe,
        StageInstance = 0xf,
        StageCommonResource = 0x10,
        StageResource = 0x11,
        Fighter1Resource = 0x12,
        Fighter2Resource = 0x13,
        Fighter3Resource = 0x14,
        Fighter4Resource = 0x15,
        Fighter1Resource2 = 0x16,
        Fighter2Resource2 = 0x17,
        Fighter3Resource2 = 0x18,
        Fighter4Resource2 = 0x19,
        FighterEffect = 0x1a,
        Fighter1Instance = 0x1b,
        Fighter2Instance = 0x1c,
        Fighter3Instance = 0x1d,
        Fighter4Instance = 0x1e,
        FighterTechqniq = 0x1f,
        FighterKirbyResource1 = 0x20,
        FighterKirbyResource2 = 0x21,
        FighterKirbyResource3 = 0x22,
        AssistFigureResource = 0x23,
        ItemExtraResource = 0x24,
        EnemyInstance = 0x25,
        PokemonResource = 0x26,
        WeaponInstance = 0x27,
        InfoInstance = 0x28,
        InfoExtraResource = 0x29,
        MenuInstance = 0x2a,
        MenuResource = 0x2b,
        CopyFB = 0x2c,
        GameGlobal = 0x2d,
        GlobalMode = 0x2e,
        MeleeFont = 0x30,
        OverlayCommon = 0x32,
        OverlayStage = 0x33,
        OverlayMenu = 0x34,
        OverlayFighter1 = 0x35,
        OverlayFighter2 = 0x36,
        OverlayFighter3 = 0x37,
        OverlayFighter4 = 0x38,
        OverlayEnemy = 0x39,
        Thread = 0x3a,
        Invalid = 0xff,

        // NON-STANDARD
        BrawlEx = 0x3b,
        Syringe = 0x3c,
        CodeMenu = 0x3d,
        FudgeAI = 0x3e,
        StockFaceResource = 0x3f,
        RetroMode = 0x40
    };
} // namespace HeapType

// using namespace Heaps;

typedef Heaps::HeapType HeapType;
typedef Heaps::HeapType srHeapType;

s32 srSystemGetDebugLevel();
void* operator new(size_t size);
void* operator new(size_t size, Heaps::HeapType heap);
void operator delete(void* ptr);
void* operator new[](size_t size, Heaps::HeapType heap);
void* operator new[](size_t size);
void operator delete[](void* ptr);
