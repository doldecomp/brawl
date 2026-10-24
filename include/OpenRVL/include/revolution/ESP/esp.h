#ifndef RVL_SDK_ESP_H
#define RVL_SDK_ESP_H
#include <revolution/ARC.h>
#include <revolution/IPC.h>
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ES_IOCTLV_LAUNCH_TITLE = 8,
    ES_IOCTLV_READ_CONTENT_FILE = 10,
    ES_IOCTLV_GET_NUM_TICKET_VIEWS = 18,
    ES_IOCTLV_GET_TICKET_VIEWS = 19,
    ES_IOCTLV_GET_DATA_DIR = 29,
    ES_IOCTLV_GET_TITLE_ID = 32,
    ES_IOCTLV_SEEK_CONTENT_FILE = 35,
} ESIoctl;

typedef u32 ESId;
typedef u64 ESTitleId;
typedef u64 ESTicketId;
typedef u8 ESVersion;
typedef u8 ESTicketReserved[48];
typedef u8 ESSysAccessMask[2];
typedef u8 ESCidxMask[64];

#pragma pack(push, 4)

typedef struct ESLpEntry {
    u32 code;  // at 0x0
    u32 limit; // at 0x4
} ESLpEntry;

typedef struct ESTicketView {
    ESVersion version;               // at 0x0
    ESTicketId ticketID;             // at 0x4
    ESId devID;                      // at 0xC
    ESTitleId titleID;               // at 0x10
    ESSysAccessMask sysAccessMask;   // at 0x18
    u16 ticketVer;                   // at 0x1A
    u32 accTitleID;                  // at 0x1C
    u32 accTitleMask;                // at 0x20
    u8 license;                      // at 0x24
    ESTicketReserved reserved;       // at 0x25
    u8 audit;                        // at 0x55
    ESCidxMask cidxMask;             // at 0x56
    ESLpEntry limits[8];             // at 0x98
} ESTicketView;

typedef struct ESTmdViewHeader {
    ESVersion version;    // at 0x0
    ESTitleId sysVersion; // at 0x4
    ESTitleId titleId;    // at 0xC
    u32 type;             // at 0x14
    u16 groupId;          // at 0x18
    u8 reserved[62];      // at 0x1A
    u16 titleVersion;     // at 0x58
    u16 numContents;      // at 0x5A
} ESTmdViewHeader;

typedef struct ESCmdView {
    u32 cid;   // at 0x0
    u16 index; // at 0x4
    u16 type;  // at 0x6
    u64 size;  // at 0x8
} ESCmdView;

typedef struct ESTmdView {
    ESTmdViewHeader head;     // at 0x0
    ESCmdView contents[512];  // at 0x5C
} ESTmdView;

typedef struct ESTitleMetaHeader {
    ESVersion version;          // at 0x0
    ESVersion caCrlVersion;     // at 0x1
    ESVersion signerCrlVersion; // at 0x2
    ESTitleId sysVersion;       // at 0x4
    ESTitleId titleId;          // at 0xC
    u32 type;                   // at 0x14
    u16 groupId;                // at 0x18
    u8 reserved[62];            // at 0x1A
    u32 accessRights;           // at 0x58
    u16 titleVersion;           // at 0x5C
    u16 numContents;            // at 0x5E
    u16 bootIndex;              // at 0x60
} ESTitleMetaHeader;

typedef struct ESContentMeta {
    u32 cid;      // at 0x0
    u16 index;    // at 0x4
    u16 type;     // at 0x6
    u64 size;     // at 0x8
    u8 hash[20];  // at 0x10
} ESContentMeta;

typedef struct ESTitleMeta {
    u8 sig[0x180];                // at 0x0
    ESTitleMetaHeader head;       // at 0x180
    ESContentMeta contents[512];  // at 0x1E4
} ESTitleMeta;

#pragma pack(pop)

typedef struct ESPTicket {
    u8 dummy[0x2A4];
} ESPTicket;

typedef struct ESPTmd {
    u8 dummy[0x49E4];
} ESPTmd;

s32 ESP_InitLib(void);
s32 ESP_CloseLib(void);
s32 ESP_LaunchTitle(ESTitleId titleId, ESTicketView* view);
s32 ESP_GetTicketViews(ESTitleId titleId, ESTicketView* views, u32* count);
s32 ESP_DiGetTicketView(const void* ticket, ESTicketView* view);
s32 ESP_DiGetTmd(ESTitleMeta* tmd, u32* size);
s32 ESP_GetTmdView(ESTitleId titleId, ESTmdView* view, u32* size);
s32 ESP_ListTitleContentsOnCard(ESTitleId titleId, u32* contents, u32* count);
s32 ESP_GetTitleId(ESTitleId* titleId);
s32 ESP_GetConsumption(ESTicketId ticketId, ESLpEntry* entries, u32* count);
s32 ESP_DeleteTitle(ESTitleId titleId);
s32 ESP_ReadContentFile(s32 fd, void* dst, u32 len);
s32 ESP_SeekContentFile(s32 fd, s32 offset, s32 origin);

#ifdef __cplusplus
}
#endif
#endif
