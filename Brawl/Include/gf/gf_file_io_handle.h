#pragma once

#include <StaticAssert.h>
#include <gf/gf_file_io_manager.h>
#include <gf/gf_file_io_request.h>
#include <memory.h>
#include <types.h>


/*
 * This class seems to be a helper wrapper around the gfFileIORequest. It handles the construction and
 * submission of the request, but doesn't hold other data of its own as far as I can tell. It is used
 * internally within gfArchive.
 * 
*/
class gfFileIOHandle {
public:
    // 0
    gfFileIORequest* m_request;

    // Stuff to check on the request once it has been started.
    bool isReady() const;
    int getReturnStatus() const;
    void* getBuffer() const;
    int getSize() const;
    const void* getPool() const;
    void release();
    bool cancelRequest();
    bool isCanceled() const;
    bool isCancelRequested() const;

    // Asynchronous "request" methods. These will craft the gfFileIORequest for you and
    // submit it to the gfFileIOManager. You are responsible for checking in on them as far as I can tell.
    bool createDirRequest(const char* filepath);
    bool checkDirRequest(const char* filepath);
    bool checkFileRequest(const char* filepath);
    bool checkFreeSize(const char* filepath);

    /*
     * Some notes about read request behavior.
     * - IMPORTANT: The addr parameter is actually the heap address. These read methods will *always* alloc your
     *   buffer for you, and I believe it is the caller's responsiblity to delete it.
     * - I'm not sure why but readRequest would hang and not ever return the correct isReady().
     *   I'm not sure if its because in my testing I was trying to read a file that I had just
     *   written, but I had no issues using readRequestNoSync. readRequestCached I did not test.
     * - The read() method is a synchronous variant of readRequestNoCached with a thread sleep loop. Nice.
     * - Setting length to 0 will read the whole file.
     * - The lengths here are in bytes.
     * - The lengths are a minimum length to read, not a maximum. If your file is too small, the read will
     *   fail. If you are worried about file size, I would probably use CheckFileSizeRequest or something along
     *   those lines. That's what the read() calls do internally.
     * - Using a filepath like "sd:/foo/bar" works.
     * - 
    */
    bool read(const char* filepath, HeapType heap, int offset);
    bool read(const char* filepath, const void* addr, int offset);
    bool read(const char* filepath, void* addr, int offset);
    bool readRequest(const char* filename, HeapType heap, int length, int offset);
    bool readRequest(const char* filepath, const void* addr, int length, int offset);
    bool readRequest(const char* filepath, void* addr, int length, int offset);
    bool readRequestCached(const char* filepath, HeapType heap, int length, int offset);
    bool readRequestCached(const char* filepath, const void* addr, int length, int offset);
    bool readRequestCached(const char* filepath, void* addr, int length, int offset);
    bool readRequestNoSync(const char* filepath, HeapType heap, int length, int offset); 
    bool readRequestNoSync(const char* filepath, void* addr, int length, int offset);
    bool findFileCountRequest(const char* filepath);
    bool findfirstRequest(const char* filepath, HeapType heap);
    bool del(const char* filepath);

    // The length is not allowed to be below 32 bytes. If the length is 0, it will create the 
    // file and write nothing. If the length is positive but below 32, it will write 32 bytes,
    // potentially over-reading your buffer.
    //
    // It is also worth mentioning that "offset" is the offset of the file to append from, not the 
    // offset in the src buffer.
    bool writeRequest(const char* filepath, void* addr, int length, int offset);
    // filepath for writeNAND seems to be "/my/file/path". It seems to be used internally to load
    // fighter misc data into NAND for some purpose.
    bool writeNAND(void* addr, int length, const char* filepath);

    bool mountSD();
    bool unmountSD();

    // the unknown param is often 0, and I suspect it's some kind of format specifier.
    // it goes to 0x15 on the request.
    bool mountVF(u8 unk, const char* filepath);
    bool createVFSystemFile(const char* filepath, int length);
    // another unknown parameter to the request's 0x15
    bool formatVF(int unk);
    bool unmountVF(u8 unk);
    gfFileIOHandle() : m_request(nullptr) { }

    ~gfFileIOHandle();

    // the gfFileIONotify seems to be an abstract class. There is a gfArchiveNotify that seems to be used to tell
    // a gfArchive that the operation is done. It seems like it's acting like a destructor and freeing a bunch of
    // stuff.
    void setNotify(void* gfFileIONotify);

    void ensureLoaded() {
        if (!m_request) {
            m_request = g_gfFileIOManager->allocRequest();
        }
    }
};
static_assert(sizeof(gfFileIOHandle) == 0x4, "Class is the wrong size!");
