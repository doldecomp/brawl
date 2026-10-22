#pragma once

#include <StaticAssert.h>
#include <revolution/OS/OSMessage.h>
#include <revolution/OS/OSThread.h>
#include <types.h>

struct THPReadBlock {
    s32 m_nextBlockSize;
    // data...
};
// TODO size

struct THPReadMessage {
    THPReadBlock* m_block;
    s32 m_blockNum;
};
// TODO size

struct THPReadWork {
    static const u32 StackSize = 0x1000;
    static const u32 BufferCap = 6;
    BOOL m_threadActive;
    OSMessageQueue m_freeReadQueue;
    OSMessageQueue m_pastReadQueue;
    OSMessageQueue m_pastRead2Queue;
    OSMessage m_freeReadBuf[BufferCap];
    OSMessage m_pastReadBuf[BufferCap];
    OSMessage m_pastRead2Buf[BufferCap];
    OSThread m_thread;
    char m_stack[StackSize];
};
static_assert(sizeof(THPReadWork) == 0x13C8, "Class is the wrong size!");

u32 GetSizeTHPReadWork();
void SetTHPReadWork(THPReadWork* work);
void FreeTHPReadWork();
bool CreateReadThread(s32 prio, void* funcArg);
void ReadThreadStart();
void ReadThreadCancel();
OSMessage PopReadedBuffer();
void PushReadedBuffer(OSMessage msg);
OSMessage PopFreeReadBuffer();
void PushFreeReadBuffer(OSMessage msg);
OSMessage PopReadedBuffer2();
void PushReadedBuffer2(OSMessage msg);
