#include <cstring>
#include <gf/gf_heap_manager.h>
#include <gf/gf_file_io_handle.h>
#include <gf/gf_file_io_manager.h>
#include <gf/gf_file_io_request.h>
#include <revolution/NET/crc.h>
#include <revolution/OS/OSMutex.h>
#include <sr/sr_common.h>
#include <types.h>

gfFileIORequestQueue::gfFileIORequestQueue() {
    OSInitMutex(&m_mtx);
    m_queue = new (Heaps::SystemFW) utQueue<gfFileIORequest*, 128>;
}

gfFileIORequest::~gfFileIORequest() {
    m_isReady = true;
    unk17_b6 = false;
    unk17_b5 = false;
    m_isCancelRequested = false;
    m_isCanceled = false;
    unk17_b2 = false;
    unk17_b1 = false;
    unk17_b0 = false;
    unk18_b7 = false;
    unk18_b6 = false;
    unk18_b5 = false;
    unk18_b4 = false;
    m_notifyCallback = nullptr;
    m_pFilepath = nullptr;
    m_filepath[0] = '\0';
}

void gfFileIORequest::setParam(const char* path) {
    m_pFilepath = nullptr;
    m_isReady = true;

    unk17_b6 = false;
    unk17_b5 = false;
    m_isCancelRequested = false;
    m_isCanceled = false;
    unk17_b2 = false;
    unk17_b1 = false;
    unk17_b0 = false;

    unk18_b7 = false;
    unk18_b6 = false;
    unk18_b5 = false;
    unk18_b4 = false;

    m_returnStatus = 0;
    m_isReady = false;

    unk17_b1 = g_gfFileIOManager->unk98;
    unk17_b5 = false;
    unk18_b5 = false;
    m_dest = nullptr;
    m_heap = nullptr;
    unk18_b4 = false;

    m_filepath[0] = '\0';
    m_crc16 = 0;
    if (path) {
        m_pFilepath = m_filepath;
        strncpy(m_filepath, path, sizeof(m_filepath) - 1);
        m_crc16 = NETCalcCRC16(m_pFilepath, strlen(m_pFilepath));
    }
}

void gfFileIORequest::setReadParam(const char* path, const void* addr, int len, int offs) {
    setParam(path);
    m_heap = addr;
    m_kind = Read;
    m_readLen = len;
    m_offset = offs;
    if (path[0] == '/' && path[1] == 'f') {
        unk18_b4 = true;
    }
}

void gfFileIORequest::setReadParam(const char* path, void* addr, int len, int offs) {
    setParam(path);
    m_dest = addr;
    m_kind = Read;
    m_readLen = len;
    m_offset = offs;
    if (path[0] == '/' && path[1] == 'f') {
        unk18_b4 = true;
    }
}

void gfFileIORequest::setWriteParam(const char* path, void* addr, int len, int offs) {
    setParam(path);
    m_kind = Write;
    m_dest = addr;
    m_heap = nullptr;
    m_readLen = len;
    m_offset = offs;
}
