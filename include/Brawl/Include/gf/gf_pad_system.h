#pragma once

#include <gf/gf_pad_queue.h>
#include <gf/gf_pad_status.h>
#include <gf/gf_rumble.h>
#include <revolution/OS/OSAlarm.h>
#include <StaticAssert.h>

#define GF_PAD_SYSTEM_GET_ALL_PADS 0xF0

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

    // of these 3, the sys pad variation is used extensively
    // throughout brawl, anywhere in any of the menus. If you 
    // ask for padNum 0xF0, you'll get the merged pad instead.
    void getDebugPadStatus(int padNum, gfPadStatus* dest);
    void getSysPadStatus(int padNum, gfPadStatus* dest);
    void getGamePadStatus(int padNum, gfPadStatus* dest);

    // This arg is &-ed with g_motorMask before applying.
    // It also checks bit 6 of _0x35 before proceeding.
    void maskMotor(u16);

    // These merge functions appear to be widely used for input that can come from any player, and
    // are also used to internally to populate the 0x844+ gfPadStatus fields.
    // The mask here lets you skip controllers based on the mask, so bit 1 being 0 means that player 1 will be skipped.
    static void merge(gfPadStatus* src, int numPads, u32 mask, gfPadStatus* dest);
    // Same as above with a mask of 0xFFFF.
    static void merge(gfPadStatus* src, int numPads, gfPadStatus* dest);

    void pauseNotify();

    // Runs 0x35 & 0x7F and passes all parameters to WPADReadGameData
    u32 readGameDataRequest(int, int, int, int);
    void setConnectCallback(int);
    // This mask is saved to 0xb58
    void startMotor(int padNum, u16 mask);
    void startMotor(int padNum); // Defaults mask to 0xFFFF
    void stopMotor(int padNum);
    void stopMotorH(int padNum); // seems identical to stopMotor.
    void stopMotorAllForce();

    void startSimpleSync(); // Runs 0x34 & 0xBF


    // This is the function where the game pads at 0x444 get updated. Some observations:
    // It is called by the IpSwitch which then uses it to record inputs
    // or presumably do network buffering and other trickery.
    //
    // It seems to check bit 3 of 0x34 to determine whether to read from the
    // sys pads or the pad queue.
    //
    // It sets bit 8 of 0x34 when it reads.
    //
    // It checks the player num bit of 0x3e before it reads.
    //
    // If 0x34 bit 1, it masks out the start button of every pad.
    //
    // If 0x3e bit 9, it zeroes the pad at 0x884
    void updateGame();

    // Runs updateLowGc() and updateLowWii()
    void updateLow();

    // appears to read some masks and do some bookkeeping to 0x944
    // Reads up to 4 gc pads.
    void updateLowGC(gfPadStatus* dest);

    // A lot more complex than updateLowWii, but similar concept.
    // Reads up to 4 wiimotes.
    void updateLowWii(gfPadStatus* dest);


    // This is called at the top of the main game loop.
    //
    // Step 1: systemPads -> debugPads
    // Step 2: debugPads -> menu conversion -> menuPads
    // Step 3: Does some bookkeeping involving unknown data area 0x944 and unknown flags 0xb48 and 0xb49
    // Step 4: debugPads & ~m_sysExcludedPadMask -> sysPadsMerged
    // Step 5: debugPads & m_debugPadMask -> debugPadsMerged
    // Step 6: menuPads -> menuPadsMerged
    // Step 7: Some motor control stuff.
    void updateSystem();

    // Sets 0xb6c to data and 0x35 bit 8 to 1
    void wpadGameDataCallback(int data);
    // Unsure about the parameters to this.
    void wpadSimpleSyncCallback();
    // Clears 0x35 bit 8, params are passed to WPADWriteGameData()
    u32 writeGameDataRequest(int, int, int, int);
    static void _alarmCallback(OSAlarm* alarm, OSContext* ctx);

    OSAlarm m_alarm;

    // mask stuff in here
    // observed with 0x00000289
    char _0x30[0x4];

    // option bitfield, observed with value 0x88.
    u8 _0x34;

    // option bitfield, observed with value 0x4C
    u8 _0x35;

    // 0x36, observed with value 0x0001
    short m_unkCounter;

    // 0x38, observed with value 0xFFFF
    u16 m_debugPadMask;

    // 0x3A, observed with value 0x0000
    u16 m_sysExcludedPadMask;

    // 0x3C, Used in updateGamePads to determine which pads go to m_gamePadMerged.
    // observed with value 0xFFFF
    u16 m_gamePadMask;

    // Observed with value 0x0000
    u16 _0x3e;

    // 0x40
    gfPadStatus m_systemPads[8];

    // 0x240
    gfPadStatusQueue* m_padQueue;

    // 0x244
    // It is unclear what the difference is between debug
    // pads and game pads, but I speculate that it has to
    // do with their devkit having separate controllers that
    // handle their debug mode stuff.
    gfPadStatus m_debugGcnPads[4];
    gfPadStatus m_debugWiiPads[4];

    // 0x444
    // Seems to be the same as the debug pads, but with
    // the start button permanently masked out. It might
    // get updated at a different time in the frame as well.
    gfPadStatus m_gameGcnPads[4];
    gfPadStatus m_gameWiiPads[4];

    // 0x644
    // These go through some conversion in gfPadStatus::convSysStatusToMenuStatus
    gfPadStatus m_menuGcnPads[4];
    gfPadStatus m_menuWiiPads[4];

    // 0x844
    gfPadStatus m_sysPadMerged;
    // 0x884
    gfPadStatus m_gamePadMerged;
    // 0x8c4
    gfPadStatus m_menuPadMerged;
    // 0x904
    gfPadStatus m_debugPadMerged;

    // 0x944
    // There's approximately 0x200 bytes of unknown structure that doesn't look
    // like pad data until about 0xb50. After that there is the rumble motor at 0xb68;
    char _0x944[0x200];

    int _0xb44;

    // Clamped to 100
    u8 _0xb48;
    // Clamped to 7
    u8 _0xb49;

    // 0xb4a, Unsure of what this does precisely, but it's
    // used in a few rumble-related functions.
    u16 m_motorMask;

    int _0xb4c[2];

    // 0xb54, is a *gfThread
    void* m_controllerThread;

    // 0xb58
    // set by startMotor() and stopMotor() per player.
    u16 m_padMotorMasks[8];

    // 0xb68
    gfRumble* m_gfRumble;

    // 0xb6c, set by wpadGameDataCallback
    int m_gameData;
    char _0xb70[8];
};
static_assert(sizeof(gfPadSystem) == 0xb78, "gfPadSystem is the wrong size!");

extern gfPadSystem* g_gfPadSystem;
