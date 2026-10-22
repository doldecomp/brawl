#pragma once

#include <StaticAssert.h>
#include <snd/snd_id.h>
#include <types.h>
#include <nw4r/snd/snd_SoundHeap.h>
#include <nw4r/snd/snd_Sound3DManager.h>
#include <nw4r/snd/snd_Sound3DListener.h>
#include <nw4r/snd/snd_DvdSoundArchive.h>
#include <nw4r/snd/snd_SoundArchivePlayer.h>

class sndHeapSys
{
public:
    char _0[0x258];
    nw4r::snd::SoundHeap m_heapArr[0xC];
    char _468[0xC];
    nw4r::snd::SoundHeap* m_heapAddresses[0xC];
    u32 m_heapMaxSizeArr[0xC];
    u32 m_heapCurrSizeArr[0xC];
};
static_assert(sizeof(sndHeapSys) == 0x504, "Class is wrong size!");

class sndSystem {
public:
    nw4r::snd::DvdSoundArchive m_dvdSoundArchive;
    nw4r::snd::SoundArchivePlayer m_archivePlayer;
    nw4r::snd::Sound3DManager m_3DManager;
    nw4r::snd::Sound3DListener m_3DListener;
    sndHeapSys* m_sndHeapSys;
    char _2D4[0x8FC];

    int loadSoundGroup(SndGroupID sndGroupId, int, bool isRequest);
    bool isSoundGroupLoaded(SndGroupID sndGroupId);
    void freeGroup(int heapLevel, int);
    bool loadArchiveHeader();
    bool setupBuffers();
    void loadCommon();

    s32 playSE(SndID sndID, int unk, int unk2, int unk3, int unk4);
    void stopSE(s32 handleId, s32 p2);
    void stopSE(s8 handleIndex, s32 p2);
    void setBGMVol(bool setImmediately, float volume);
    void setEffectVol(bool unused, bool setImmediately, float volume);
    s32 prepareSE(SndID p1, s32 p2, s32 p3);
    void setPan(s32 p1, float p2);
    void startSE(s32 p1, s32 p2, s32 p3);
    bool isPlay(s32 handleId);
    bool isPlaySEID(SndID sndID);
    bool playBGM(int bgmId, u32 fade, bool);
    int getBGMId();
    void specialPause();
    void specialResume();

    static SndID constructInterceptSndID(int wavID, SndID infoSndID) { // custom
        return static_cast<SndID>(0xF0000000 + ((wavID & 0xFFF) << 16) + infoSndID);
    }
};
static_assert(sizeof(sndSystem) == 0xbd0, "Class is wrong size!");

extern sndSystem* g_sndSystem;
