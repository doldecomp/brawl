#pragma once

#include <revolution/OS/OSMessage.h>
#include <revolution/OS/OSThread.h>
#include <types.h>

// TODO type
struct AudioDecMessage {
    void* unk0;
    u32 unk4;
    u32 unk8;
    u8 unkC[0xC];
};
// TODO size assertion

struct THPReadBuffer {
    static void AudioDecode(AudioDecMessage*);
};

// TODO type
struct THPAudioDecWork {
    static const u32 StackSize = 0x1000;
    static const u32 BufferCap = 6;
    BOOL m_threadActive;
    OSThread m_thread;
    char m_stack[StackSize]; // 0x320
    OSMessageQueue m_freeAudioQueue;
    OSMessageQueue m_decodedAudioQueue;
    OSMessage m_freeAudioBuf[BufferCap];
    OSMessage m_decodedAudioBuf[BufferCap];
};
// TODO size assertion

u32 GetSizeTHPAudioDecWork();
void SetTHPAudioDecWork(THPAudioDecWork* work);
void FreeTHPAudioDecWork();
bool CreateAudioDecodeThread(s32 prio, void* funcArg);
void AudioDecodeThreadStart();
void AudioDecodeThreadCancel();
void* AudioDecoder(void* p1);
void* AudioDecoderForOnMemory(void* p1);
void PushFreeAudioBuffer(OSMessage p1);
OSMessage PopDecodedAudioBuffer(u32 flags);
