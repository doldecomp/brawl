#include <gf/gf_callback.h>
#include <gf/gf_error_check.h>
#include <gf/gf_error_manager.h>
#include <gf/gf_file_io.h>
#include <revolution/DVD/dvd.h>
#include <revolution/DVD/dvdidutils.h>
#include <types.h>

static gfErrorCheckCallback g_errorCheckCb;

void gfErrorCheck::init() {
    gfFileIO::setFatalErrorCallback(&g_errorCheckCb);
}

void gfErrorCheck::check() {
    s32 status = DVDGetDriveStatus();
    u32 r31;
    bool r30 = false;
    if (status == -1) {
        r30 = true;
        r31 = 4;
    } else if (status == 4) {
        r30 = true;
        r31 = 1;
    } else if (status == 11) {
        r30 = true;
        r31 = 3;
    } else if (status == 6) {
        r30 = true;
        r31 = 2;
    } else {
        const DVDDiskID* id1 = DVDGetCurrentDiskID();
        const DVDDiskID* id2 = gfFileIO::getDVDDiskId();
        if (true != DVDCompareDiskID(id1, id2)) {
            r30 = true;
            r31 = 2;
        }
    }

    if (r30) {
        gfErrorManager::getInstance()->notifyError(r31, 0);
    } else {
        gfErrorManager::getInstance()->notifyErrorRecovery(false);
    }
}
