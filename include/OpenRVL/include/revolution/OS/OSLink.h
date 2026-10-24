#ifndef RVL_SDK_OS_LINK_H
#define RVL_SDK_OS_LINK_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

#define OS_MODULE_VERSION 3

#define OS_SECTIONINFO_EXEC 0x1
#define OS_SECTIONINFO_OFFSET(offset) ((offset) & ~OS_SECTIONINFO_EXEC)

typedef enum {
    R_DOLPHIN_NOP = 201,
    R_DOLPHIN_SECTION = 202,
    R_DOLPHIN_END = 203,
    R_DOLPHIN_MRKREF = 204,
} OSDolphinRelocType;

typedef u32 OSModuleID;
typedef struct OSModuleInfo OSModuleInfo;

typedef struct OSModuleLink {
    OSModuleInfo* next; // at 0x0
    OSModuleInfo* prev; // at 0x4
} OSModuleLink;

typedef struct OSModuleQueue {
    OSModuleInfo* head; // at 0x0
    OSModuleInfo* tail; // at 0x4
} OSModuleQueue;

struct OSModuleInfo {
    OSModuleID id;         // at 0x0
    OSModuleLink link;     // at 0x4
    u32 numSections;       // at 0xC
    u32 sectionInfoOffset; // at 0x10
    u32 nameOffset;        // at 0x14
    u32 nameSize;          // at 0x18
    u32 version;           // at 0x1C
};

typedef struct OSModuleHeader {
    OSModuleInfo info;     // at 0x0
    u32 bssSize;           // at 0x20
    u32 relOffset;         // at 0x24
    u32 impOffset;         // at 0x28
    u32 impSize;           // at 0x2C
    u8 prologSection;      // at 0x30
    u8 epilogSection;      // at 0x31
    u8 unresolvedSection;  // at 0x32
    u8 bssSection;         // at 0x33
    u32 prolog;            // at 0x34
    u32 epilog;            // at 0x38
    u32 unresolved;        // at 0x3C
    u32 align;             // at 0x40
    u32 bssAlign;          // at 0x44
    u32 fixSize;           // at 0x48
} OSModuleHeader;

typedef struct OSSectionInfo {
    u32 offset; // at 0x0
    u32 size;   // at 0x4
} OSSectionInfo;

typedef struct OSImportInfo {
    OSModuleID id; // at 0x0
    u32 offset;    // at 0x4
} OSImportInfo;

typedef struct OSRel {
    u16 offset;  // at 0x0
    u8 type;     // at 0x2
    u8 section;  // at 0x3
    u32 addend;  // at 0x4
} OSRel;

#define OSGetSectionInfo(module)                                               \
    ((OSSectionInfo*)((OSModuleInfo*)(module))->sectionInfoOffset)

void OSNotifyLink(OSModuleInfo* module);
void OSNotifyUnlink(OSModuleInfo* module);
void OSNotifyPreLink(OSModuleHeader* newModule, OSModuleHeader* module);
void OSNotifyPostLink(OSModuleHeader* newModule, OSModuleHeader* module);

void OSSetStringTable(void* table);
BOOL OSLink(OSModuleInfo* newModule, void* bss);
BOOL OSLinkFixed(OSModuleInfo* newModule, void* bss);
BOOL OSUnlink(OSModuleInfo* oldModule);
void __OSModuleInit(void);
OSModuleInfo* OSSearchModule(void* ptr, u32* section, u32* offset);

#ifdef __cplusplus
}
#endif
#endif
