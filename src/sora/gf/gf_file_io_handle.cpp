#include <revolution/OS/OSInterrupt.h>
#include <gf/gf_heap_manager.h>
#include <gf/gf_file_io_handle.h>
#include <gf/gf_file_io_manager.h>
#include <gf/gf_file_io_request.h>
#include <sr/sr_common.h>
#include <types.h>

#pragma dont_inline on
gfFileIOHandle::~gfFileIOHandle() {
    if (m_request) {
        release();
    }
}
#pragma dont_inline reset

void gfFileIOHandle::setNotify(void* notify) {
    ensureLoaded();
    m_request->m_notifyCallback = notify;
}

bool gfFileIOHandle::createDirRequest(const char* filepath) {
    ensureLoaded();
    if (m_request) {
        m_request->setParam(filepath);
        m_request->m_kind = gfFileIORequest::CreateDir;
        m_request->unk17_b1 = false;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::checkFileRequest(const char* filepath) {
    ensureLoaded();
    if (m_request) {
        m_request->setParam(filepath);
        m_request->m_heap = nullptr;
        m_request->m_kind = gfFileIORequest::CheckFile;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::findfirstRequest(const char* filepath, HeapType heap) {
    void* heapPtr = gfHeapManager::getHeap(heap);
    ensureLoaded();
    if (m_request) {
        m_request->setParam(filepath);
        m_request->m_heap = heapPtr;
        m_request->m_kind = gfFileIORequest::FindFirst;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::findFileCountRequest(const char* filepath) {
    ensureLoaded();
    if (m_request) {
        m_request->setParam(filepath);
        m_request->m_kind = gfFileIORequest::FindFileCount;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::checkDirRequest(const char* filepath) {
    ensureLoaded();
    if (m_request) {
        m_request->setParam(filepath);
        m_request->m_kind = gfFileIORequest::CheckDir;
        m_request->unk17_b1 = false;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::createVFSystemFile(const char* filepath, int length) {
    ensureLoaded();
    if (m_request) {
        m_request->setParam(filepath);
        m_request->m_kind = gfFileIORequest::CreateVFSystemFile;
        m_request->m_readLen = length;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::mountVF(u8 p1, const char* filepath) {
    ensureLoaded();
    if (m_request) {
        m_request->setParam(filepath);
        m_request->m_kind = gfFileIORequest::MountVF;
        m_request->m_vfUnk = p1;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::unmountVF(u8 p1) {
    ensureLoaded();
    if (m_request) {
        m_request->setParam(nullptr);
        m_request->m_kind = gfFileIORequest::UnmountVF;
        m_request->m_vfUnk = p1;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::formatVF(int p1) {
    ensureLoaded();
    if (m_request) {
        m_request->setParam(nullptr);
        m_request->m_kind = gfFileIORequest::FormatVF;
        m_request->m_vfUnk = p1;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::mountSD() {
    ensureLoaded();
    if (m_request) {
        m_request->setParam(nullptr);
        m_request->m_kind = gfFileIORequest::MountSD;
        m_request->m_vfUnk = 0;
        m_request->unk17_b1 = false;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::unmountSD() {
    ensureLoaded();
    if (m_request) {
        m_request->setParam(nullptr);
        m_request->m_kind = gfFileIORequest::UnmountSD;
        m_request->m_vfUnk = 0;
        m_request->unk17_b1 = false;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}


bool gfFileIOHandle::checkFreeSize(const char* filepath) {
    ensureLoaded();
    if (m_request) {
        m_request->setParam(filepath);
        m_request->m_kind = gfFileIORequest::CheckFreeSize;
        m_request->m_vfUnk = 0;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::del(const char* filepath) {
    ensureLoaded();
    if (m_request) {
        m_request->setParam(filepath);
        m_request->m_kind = gfFileIORequest::Del;
        m_request->m_vfUnk = 0;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::writeNAND(void* addr, int length, const char* filepath) {
    ensureLoaded();
    m_request->setParam(filepath);
    m_request->m_kind = gfFileIORequest::WriteNAND;
    m_request->m_readLen = length;
    m_request->m_dest = addr;
    m_request->m_offset = 0;
    g_gfFileIOManager->push(m_request);
    return true;
}

bool gfFileIOHandle::readRequest(const char* filepath, HeapType heap, int length, int offset) {
    const void* heapPtr = gfHeapManager::getHeap(heap);
    ensureLoaded();
    if (m_request) {
        m_request->setReadParam(filepath, heapPtr, length, offset);
        m_request->unk18_b5 = true;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::readRequest(const char* filepath, const void* heapPtr, int length, int offset) {
    ensureLoaded();
    if (m_request) {
        m_request->setReadParam(filepath, heapPtr, length, offset);
        m_request->unk18_b5 = true;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::readRequest(const char* filepath, void* heapPtr, int length, int offset) {
    ensureLoaded();
    if (m_request) {
        m_request->setReadParam(filepath, heapPtr, length, offset);
        m_request->unk18_b5 = true;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::readRequestCached(const char* filepath, HeapType heap, int length, int offset) {
    const void* heapPtr = gfHeapManager::getHeap(heap);
    ensureLoaded();
    if (m_request) {
        m_request->setReadParam(filepath, heapPtr, length, offset);
        m_request->m_isCached = true;
        m_request->unk18_b5 = true;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::readRequestCached(const char* filepath, const void* heapPtr, int length, int offset) {
    ensureLoaded();
    if (m_request) {
        m_request->setReadParam(filepath, heapPtr, length, offset);
        m_request->m_isCached = true;
        m_request->unk18_b5 = true;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::readRequestCached(const char* filepath, void* heapPtr, int length, int offset) {
    ensureLoaded();
    if (m_request) {
        m_request->setReadParam(filepath, heapPtr, length, offset);
        m_request->m_isCached = true;
        m_request->unk18_b5 = true;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::readRequestNoSync(const char* filepath, HeapType heap, int length, int offset) {
    const void* heapPtr = gfHeapManager::getHeap(heap);
    ensureLoaded();
    if (m_request) {
        m_request->setReadParam(filepath, heapPtr, length, offset);
        m_request->unk17_b1 = false;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::readRequestNoSync(const char* filepath, void* heapPtr, int length, int offset) {
    ensureLoaded();
    if (m_request) {
        m_request->setReadParam(filepath, heapPtr, length, offset);
        m_request->unk17_b1 = false;
        g_gfFileIOManager->push(m_request);
        return true;
    }
    return false;
}

bool gfFileIOHandle::read(const char* filepath, HeapType heap, int offset) {
    const void* heapPtr = gfHeapManager::getHeap(heap);
    ensureLoaded();
    m_request->setReadParam(filepath, heapPtr, 0, offset);
    m_request->unk17_b1 = false;
    m_request->unk18_b7 = true;
    g_gfFileIOManager->push(m_request);

    goto loop;
sleep:
    OSSleepTicks((OS_BUS_CLOCK_SPEED / 4) / 1000);
loop:
    if (isReady()) {
        goto end;
    }
    goto sleep;
end:
    return !getReturnStatus();
}

bool gfFileIOHandle::read(const char* filepath, const void* heapPtr, int offset) {
    ensureLoaded();
    m_request->setReadParam(filepath, heapPtr, 0, offset);
    m_request->unk17_b1 = false;
    m_request->unk18_b7 = true;
    g_gfFileIOManager->push(m_request);

    goto loop;
sleep:
    OSSleepTicks((OS_BUS_CLOCK_SPEED / 4) / 1000);
loop:
    if (isReady()) {
        goto end;
    }
    goto sleep;
end:
    return !getReturnStatus();
}

bool gfFileIOHandle::read(const char* filepath, void* heapPtr, int offset) {
    ensureLoaded();
    m_request->setReadParam(filepath, heapPtr, 0, offset);
    m_request->unk17_b1 = false;
    m_request->unk18_b7 = true;
    g_gfFileIOManager->push(m_request);

    goto loop;
sleep:
    OSSleepTicks((OS_BUS_CLOCK_SPEED / 4) / 1000);
loop:
    if (isReady()) {
        goto end;
    }
    goto sleep;
end:
    return !getReturnStatus();
}

bool gfFileIOHandle::writeRequest(const char* filepath, void* heapPtr, int length, int offset) {
    ensureLoaded();
    m_request->setWriteParam(filepath, heapPtr, length, offset);
    m_request->unk17_b1 = false;
    g_gfFileIOManager->push(m_request);
    return true;
}

bool gfFileIOHandle::cancelRequest() {
    bool res = false;
    if (m_request) {
        if (!m_request->m_isCancelRequested) {
            int status = OSDisableInterrupts();
            bool r30 = m_request->unk17_b5;
            if (!r30) {
                m_request->m_isCancelRequested = true;
            }
            OSRestoreInterrupts(status);
            if (r30) {
                if (!m_request->m_kind && m_request->m_heap && m_request->m_dest) {
                    gfHeapManager::free(m_request->m_dest);
                    m_request->m_dest = nullptr;
                    m_request->m_isCancelRequested = true;
                    m_request->m_isCanceled = true;
                    m_request->m_isReady = true;
                } else {
                    m_request->m_isCancelRequested = true;
                    m_request->m_isCanceled = true;
                }
            }
            res = true;
        }
        m_request->m_notifyCallback = nullptr;
    }
    return res;
}

bool gfFileIOHandle::isCancelRequested() const {
    return m_request && m_request->m_isCancelRequested;
}

bool gfFileIOHandle::isCanceled() const {
    bool res = false;
    if (m_request->m_isCanceled) {
        res = true;
    }
    return res;
}

bool gfFileIOHandle::isReady() const {
    return m_request == nullptr ? true : m_request->m_isReady == true;
}

int gfFileIOHandle::getReturnStatus() const {
    return !m_request ? 21 : m_request->m_returnStatus;
}

int gfFileIOHandle::getSize() const {
    return m_request->m_readLen;
}

void* gfFileIOHandle::getBuffer() const {
    return m_request->m_dest;
}

const void* gfFileIOHandle::getPool() const {
    return m_request->m_heap;
}

void gfFileIOHandle::release() {
    if (m_request) {
        bool r31 = true;
        if (m_request->m_isCancelRequested && !m_request->m_isCanceled) {
            int status = OSDisableInterrupts();
            if (!m_request->m_isCanceled) {
                m_request->unk17_b2 = true;
                m_request->m_notifyCallback = nullptr;
                r31 = false;
            }
            OSRestoreInterrupts(status);
        }
        if (r31) {
            g_gfFileIOManager->freeRequest(m_request);
        }
        m_request->m_notifyCallback = nullptr;
        m_request = nullptr;
    }
}
