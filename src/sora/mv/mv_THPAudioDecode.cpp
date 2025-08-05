#include <mv/mv_THPAudioDecode.h>
#include <mv/mv_THPPlayer.h>
#include <mv/mv_THPRead.h>
#include <mv/THPAudio.h>
#include <revolution/DVD/dvd.h>
#include <revolution/OS/OSMessage.h>
#include <revolution/OS/OSThread.h>
#include <types.h>

// UBFIX: Several files should be revisited to fix types and casting

static THPAudioDecWork* g_audioDecWork;

u32 GetSizeTHPAudioDecWork() {
    return sizeof(THPAudioDecWork);
}

void SetTHPAudioDecWork(THPAudioDecWork* work) {
    if (!g_audioDecWork) {
        g_audioDecWork = work;
        work->m_threadActive = false;
    }
}

void FreeTHPAudioDecWork() {
    g_audioDecWork = nullptr;
}

bool CreateAudioDecodeThread(s32 prio, void* funcArg) {
    if (funcArg) {
        if (!OSCreateThread(&g_audioDecWork->m_thread, AudioDecoderForOnMemory,
            funcArg, g_audioDecWork->m_stack + THPAudioDecWork::StackSize,
            THPAudioDecWork::StackSize, prio, 1)) {
            return false;
        }
    } else {
        if (!OSCreateThread(&g_audioDecWork->m_thread, AudioDecoder, nullptr,
            g_audioDecWork->m_stack + THPAudioDecWork::StackSize, THPAudioDecWork::StackSize,
            prio, 1)) {
            return false;
        }
    }
    OSInitMessageQueue(&g_audioDecWork->m_freeAudioQueue,
        g_audioDecWork->m_freeAudioBuf, THPAudioDecWork::BufferCap);
    OSInitMessageQueue(&g_audioDecWork->m_decodedAudioQueue,
        g_audioDecWork->m_decodedAudioBuf, THPAudioDecWork::BufferCap);
    g_audioDecWork->m_threadActive = true;
    return true;
}

void AudioDecodeThreadStart() {
    if (g_audioDecWork->m_threadActive) {
        OSResumeThread(&g_audioDecWork->m_thread);
    }
}

void AudioDecodeThreadCancel() {
    if (g_audioDecWork->m_threadActive) {
        OSCancelThread(&g_audioDecWork->m_thread);
        g_audioDecWork->m_threadActive = false;
    }
}

void* AudioDecoder(void* p1) {
    AudioDecMessage* r30;
    s32 r29 = 0;
    while (true) {
        r30 = static_cast<AudioDecMessage*>(PopReadedBuffer());
        THPReadBuffer::AudioDecode(r30);
        if (r29 < 2 && !(g_thpObject.unkA6 & 0x1)) {
            u32 x = r30->unk4 + g_thpObject.unkC0;
            if (x == (g_thpObject.unk50 - 1)) {
                PrepareReady(true);
            }
        }
        if (r29 == 2) {
            PrepareReady(true);
        }
        PushReadedBuffer2(static_cast<OSMessage>(r30));
        r29++;
    }
}

void* AudioDecoderForOnMemory(void* p1) {
    AudioDecMessage msg;
    msg.unk0 = p1;
    s32 r31 = 0;
    const UnkTHPClass* r30 = &g_thpObject;
    u32 r29 = r30->unkBC;
    while (true) {
        msg.unk4 = r31;
        THPReadBuffer::AudioDecode(&msg);
        u32 r3 = (r31 + r30->unkC0) % r30->unk50;
        if (r3 == (r30->unk50 - 1)) {
            if (r30->unkA6 & 0x1) {
                r29 = *static_cast<u32*>(msg.unk0);
                msg.unk0 = r30->unkB4;
            } else {
                if (r31 < 2) {
                    PrepareReady(true);
                }
                OSSuspendThread(&g_audioDecWork->m_thread);
            }
        } else {
            u32 r4 = *static_cast<u32*>(msg.unk0);
            msg.unk0 = static_cast<char*>(msg.unk0) + r29;
            r29 = r4;
        }
        if (r31 == 2) {
            PrepareReady(true);
        }
        r31++;
    }
}

void THPReadBuffer::AudioDecode(AudioDecMessage* p1) {
    AudioDecMessage* r30;
    u32* r29 = static_cast<u32*>(p1->unk0) + 2;
    u32* r28 = static_cast<u32*>(p1->unk0) + g_thpObject.unk6C.length + 2;
    AudioDecMessage* msg;
    OSReceiveMessage(&g_audioDecWork->m_freeAudioQueue, (OSMessage*)&msg, OS_MSG_BLOCKING);
    u32 count = g_thpObject.unk6C.length;
    r30 = msg;
    void* r4;
    u32 i = 0;
    while (i < count) {
        switch (g_thpObject.unk6C.buf[i]) {
            case 1:
                r4 = reinterpret_cast<char*>(r28) + (*r29 * g_thpObject.unkDC);
                r30->unk8 = THPAudioDecode(r30->unk0, r4, 0);
                r30->unk4 = (u32)r30->unk0;
                OSSendMessage(&g_audioDecWork->m_decodedAudioQueue, r30, OS_MSG_BLOCKING);
                return;
            default:
                break;
        }
        u32 r0 = *r29++;
        i++;
        r28 = reinterpret_cast<u32*>(reinterpret_cast<char*>(r28) + r0);
    }
}

void PushFreeAudioBuffer(OSMessage p1) {
    OSSendMessage(&g_audioDecWork->m_freeAudioQueue, p1, 0);
}

OSMessage PopDecodedAudioBuffer(u32 flags) {
    OSMessage msg;
    if (OSReceiveMessage(&g_audioDecWork->m_decodedAudioQueue, &msg, flags) == true) {
        return msg;
    }
    return nullptr;
}
