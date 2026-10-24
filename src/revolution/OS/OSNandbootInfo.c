#include <revolution/NAND.h>
#include <revolution/OS.h>
#include <string.h>

#define NANDBOOTINFO_PATH "/shared2/sys/NANDBOOTINFO"
#define NANDBOOTINFO_PERM (NAND_PERM_RWALL)

#define OS_NANDBOOT_INFO_VALID (*(u8*)OSPhysicalToCached(0x3186))

static u32 CheckSum(OSNandbootInfo* info) {
    u32 *ptr, i, sum;

    ptr = &info->ArgOffset;
    sum = 0;

    for (i = 0; i < (sizeof(OSNandbootInfo) - 4) / 4; i++) {
        sum += *ptr;
        ptr++;
    }

    return sum;
}

BOOL __OSCreateNandbootInfo(void) {
    NANDStatus status;
    s32 result;

    result = NANDPrivateGetStatus(NANDBOOTINFO_PATH, &status);
    if (result == NAND_RESULT_OK && status.perm == NANDBOOTINFO_PERM) {
        return TRUE;
    } else if (result == NAND_RESULT_OK && status.perm != NANDBOOTINFO_PERM) {
        result = NANDPrivateDelete(NANDBOOTINFO_PATH);
        if (result != NAND_RESULT_OK) {
            return FALSE;
        }
    } else if (result == NAND_RESULT_NOEXISTS) {
        ;
    } else {
        return FALSE;
    }

    result = NANDPrivateCreate(NANDBOOTINFO_PATH, NANDBOOTINFO_PERM, 0);
    if (result != NAND_RESULT_OK) {
        return FALSE;
    }

    return TRUE;
}

BOOL __OSWriteNandbootInfo(OSNandbootInfo* info) {
    NANDFileInfo file;
    s32 result;

    info->CheckSum = CheckSum(info);

    result = NANDPrivateOpen(NANDBOOTINFO_PATH, &file, NAND_ACCESS_WRITE);
    if (result == NAND_RESULT_OK) {
        result = NANDWrite(&file, info, sizeof(OSNandbootInfo));
        if (result != sizeof(OSNandbootInfo)) {
            NANDClose(&file);
            return FALSE;
        }

        result = NANDClose(&file);
        if (result != NAND_RESULT_OK) {
            return FALSE;
        }
    } else {
        return FALSE;
    }

    return TRUE;
}

BOOL __OSGetNandbootInfoHeader(OSNandbootInfoHeader* header) {
    NANDFileInfo file;
    u8 args[0x100] ALIGN(32);
    OSNandbootInfoHeader buf ALIGN(32);
    u32 *ptr, i, j, sum;

    memset(header, 0, sizeof(OSNandbootInfoHeader));

    if (NANDPrivateOpen(NANDBOOTINFO_PATH, &file, NAND_ACCESS_READ) !=
        NAND_RESULT_OK) {
        return FALSE;
    }

    if (NANDRead(&file, &buf, sizeof(OSNandbootInfoHeader)) !=
        sizeof(OSNandbootInfoHeader)) {
        NANDClose(&file);
        return FALSE;
    }

    ptr = &buf.ArgOffset;
    sum = 0;
    for (i = 0; i < (sizeof(OSNandbootInfoHeader) - 4) / 4; i++) {
        sum += *ptr;
        ptr++;
    }

    for (i = 0; i < sizeof(((OSNandbootInfo*)NULL)->args) / sizeof(args);
         i++) {
        if (NANDRead(&file, args, sizeof(args)) != (s32)sizeof(args)) {
            NANDClose(&file);
            return FALSE;
        }

        ptr = (u32*)args;
        for (j = 0; j < sizeof(args) / 4; j++) {
            sum += *ptr;
            ptr++;
        }
    }

    if (NANDClose(&file) != NAND_RESULT_OK) {
        return FALSE;
    }

    if (buf.CheckSum == sum) {
        memcpy(header, &buf, sizeof(OSNandbootInfoHeader));
        return TRUE;
    }

    return FALSE;
}

u64 OSGetLastTitleId(void) {
    OSNandbootInfoHeader header;
    u64 titleId = 0;

    if (OS_NANDBOOT_INFO_VALID && __OSGetNandbootInfoHeader(&header)) {
        titleId = header.LastTitleId;
    }

    return titleId;
}
