#pragma once

#include <StaticAssert.h>
#include <gf/gf_pad_queue.h>
#include <gf/gf_pad_status.h>
#include <gf/gf_rumble.h>
#include <revolution/OS/OSAlarm.h>
#include <types.h>

// Replacement for the BrawlHeaders version: the layout of gfPadSystem there is
// inaccurate (the pad arrays are 8 entries wide, the thread/flag fields differ).

#define GF_PAD_SYSTEM_GET_ALL_PADS 0xF0

class gfPadReadThread;

// Bitfields are allocated MSB first by MWCC
struct PadFlags34 {
    u8 f7 : 1; // game pads have been read this frame
    u8 f6 : 1; // simple sync callback fired
    u8 f5 : 1;
    u8 f4 : 1;
    u8 f3 : 1; // read game pads from the pad queue
    u8 f2 : 1;
    u8 f1 : 1;
    u8 f0 : 1;
};

struct PadFlags35 {
    u8 f7 : 1; // game data callback fired
    u8 f6 : 1; // rumble enabled
    u8 f5 : 1;
    u8 f4 : 1;
    u8 f3 : 1;
    u8 f2 : 1;
    u8 f1 : 1;
    u8 f0 : 1;
};

class gfPadSystem {
public:
    gfPadSystem();
    void clearPadEdgeRepert();
    void clearPadQueue();
    void consumeFrameCounter(int frames);
    static gfPadSystem* create();
    void createRumbleSystem();
    void disconectWiiControler();
    u32 getGamePadQueueCount();
    int getDebugPadStatus(int padNum, gfPadStatus* dest);
    int getSysPadStatus(int padNum, gfPadStatus* dest);
    int getGamePadStatus(int padNum, gfPadStatus* dest);
    void maskMotor(u16);
    static void merge(gfPadStatus* src, int numPads, u32 mask, gfPadStatus* dest);
    static void merge(gfPadStatus* src, int numPads, gfPadStatus* dest);
    void pauseNotify();
    bool readGameDataRequest(int, int, int, int);
    void setConnectCallback(int);
    void startMotor(int padNum, u16 mask);
    void startMotor(int padNum);
    void stopMotor(int padNum);
    void stopMotorH(int padNum);
    void stopMotorAllForce();
    bool startSimpleSync();
    void updateGame();
    void updateLow();
    void updateLowGC(gfPadStatus* dest);
    void updateLowWii(gfPadStatus* dest);
    void updateSystem();
    static void wpadGameDataCallback(int chan, int data);
    static void wpadSimpleSyncCallback(int result);
    bool writeGameDataRequest(int, int, int, int);
    static void _alarmCallback(OSAlarm* alarm, OSContext* ctx);

    OSAlarm m_alarm;                  // 0x00
    int m_frameCounter;               // 0x30
    PadFlags34 m_flags34;             // 0x34
    PadFlags35 m_flags35;             // 0x35
    u16 m_unkCounter;                 // 0x36
    u16 m_debugPadMask;               // 0x38
    u16 m_sysExcludedPadMask;         // 0x3A
    u16 m_gamePadMask;                // 0x3C
    u16 m_0x3e;                       // 0x3E
    gfPadStatus m_sysPads[8];         // 0x40
    gfPadStatusQueue* m_padQueue;     // 0x240
    gfPadStatus m_debugPads[8];       // 0x244
    gfPadStatus m_gamePads[8];        // 0x444
    gfPadStatus m_menuPads[8];        // 0x644
    gfPadStatus m_sysPadMerged;       // 0x844
    gfPadStatus m_gamePadMerged;      // 0x884
    gfPadStatus m_menuPadMerged;      // 0x8C4
    gfPadStatus m_debugPadMerged;     // 0x904
    int m_0x944;                      // 0x944
    u8 m_repeatCount[8][32];          // 0x948
    u8 m_unkCount[8][32];             // 0xA48
    u8 m_repeatDelay;                 // 0xB48
    u8 m_repeatBits;                  // 0xB49
    u16 m_motorMask;                  // 0xB4A
    int m_0xb4c[2];                   // 0xB4C
    gfPadReadThread* m_controllerThread; // 0xB54
    u16 m_padMotorMasks[8];           // 0xB58
    gfRumble* m_gfRumble;             // 0xB68
    int m_gameData;                   // 0xB6C
    int m_0xb70;                      // 0xB70
    int m_0xb74;                      // 0xB74
};

static_assert(sizeof(gfPadSystem) == 0xb78, "gfPadSystem is the wrong size!");

extern gfPadSystem* g_gfPadSystem;
