#include <mv/mv_THPPlayer.h>
#include <mv/mv_THPRead.h>
#include <revolution/DVD/dvdfs.h>
#include <revolution/OS/OSMessage.h>
#include <revolution/OS/OSThread.h>
#include <types.h>

static THPReadWork* g_readWork;

u32 GetSizeTHPReadWork() {
    return sizeof(THPReadWork);
}

void SetTHPReadWork(THPReadWork* work) {
    if (!g_readWork) {
        g_readWork = work;
        work->m_threadActive = false;
    }
}

void FreeTHPReadWork() {
    g_readWork = nullptr;
}

static void* Reader(void* arg);

bool CreateReadThread(s32 prio) {
    if (!OSCreateThread(&g_readWork->m_thread, Reader,
        nullptr, g_readWork->m_stack + THPReadWork::StackSize,
        THPReadWork::StackSize, prio, OS_THREAD_DETACHED)) {
        return false;
    }
    OSInitMessageQueue(&g_readWork->m_freeReadQueue,
        g_readWork->m_freeReadBuf, THPReadWork::BufferCap);
    OSInitMessageQueue(&g_readWork->m_pastReadQueue,
        g_readWork->m_pastReadBuf, THPReadWork::BufferCap);
    OSInitMessageQueue(&g_readWork->m_pastRead2Queue,
        g_readWork->m_pastRead2Buf, THPReadWork::BufferCap);
    g_readWork->m_threadActive = true;
    return true;
}

void ReadThreadStart() {
    if (g_readWork->m_threadActive) {
        OSResumeThread(&g_readWork->m_thread);
    }
}

void ReadThreadCancel() {
    if (g_readWork->m_threadActive) {
        OSCancelThread(&g_readWork->m_thread);
        g_readWork->m_threadActive = false;
    }
}

static void* Reader(void* arg) {
    s32 offs = g_thpObject.unkB8;
    s32 size = g_thpObject.unkBC;
    s32 i = 0;
    while (true) {
        THPReadMessage* readMsg = reinterpret_cast<THPReadMessage*>(PopFreeReadBuffer());
        s32 bytesRead = DVDReadPrio(&g_thpObject.m_fInfo, readMsg->m_block, size, offs, 2);
        if (bytesRead != size) {
            if (bytesRead == DVD_RESULT_FATAL)
                g_thpObject.unkA8 = -1;
            if (i == 0)
                PrepareReady(false);
            OSSuspendThread(&g_readWork->m_thread);
        }
        readMsg->m_blockNum = i;
        PushReadedBuffer(readMsg);
        offs += size;
        size = readMsg->m_block->m_nextBlockSize;

        u32 pos = (i + g_thpObject.unkC0) % g_thpObject.unk50;
        if (pos == (g_thpObject.unk50 - 1)) {
            if (g_thpObject.unkA6 & 0x1)
                offs = g_thpObject.unk64;
            else
                OSSuspendThread(&g_readWork->m_thread);
        }
        i++;
    }
}

OSMessage PopReadedBuffer() {
    OSMessage msg;
    OSReceiveMessage(&g_readWork->m_pastReadQueue, &msg, OS_MSG_BLOCKING);
    return msg;
}

void PushReadedBuffer(OSMessage msg) {
    OSSendMessage(&g_readWork->m_pastReadQueue, msg, OS_MSG_BLOCKING);
}

OSMessage PopFreeReadBuffer() {
    OSMessage msg;
    OSReceiveMessage(&g_readWork->m_freeReadQueue, &msg, OS_MSG_BLOCKING);
    return msg;
}

void PushFreeReadBuffer(OSMessage msg) {
    OSSendMessage(&g_readWork->m_freeReadQueue, msg, OS_MSG_BLOCKING);
}

OSMessage PopReadedBuffer2() {
    OSMessage msg;
    OSReceiveMessage(&g_readWork->m_pastRead2Queue, &msg, OS_MSG_BLOCKING);
    return msg;
}

void PushReadedBuffer2(OSMessage msg) {
    OSSendMessage(&g_readWork->m_pastRead2Queue, msg, OS_MSG_BLOCKING);
}
