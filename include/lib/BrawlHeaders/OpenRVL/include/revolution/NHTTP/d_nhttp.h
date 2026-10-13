#ifndef RVL_SDK_D_NHTTP_H
#define RVL_SDK_D_NHTTP_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    NHTTP_ERROR_SYSTEM = -1,
    NHTTP_ERROR_NONE = 0,
    NHTTP_ERROR_ALLOC = 1,
    NHTTP_ERROR_TOOMANYREQ = 2,
    NHTTP_ERROR_SOCKET = 3,
    NHTTP_ERROR_DNS = 4,
    NHTTP_ERROR_CONNECT = 5,
    NHTTP_ERROR_BUFFULL = 6,
    NHTTP_ERROR_HTTPPARSE = 7,
    NHTTP_ERROR_CANCELED = 8,
    NHTTP_ERROR_REVOLUTIONSDK = 9,
    NHTTP_ERROR_REVOLUTIONWIFI = 10,
    NHTTP_ERROR_UNKNOWN = 11,
    NHTTP_ERROR_DNS_PROXY = 12,
    NHTTP_ERROR_CONNECT_PROXY = 13,
    NHTTP_ERROR_SSL = 14,
    NHTTP_ERROR_BUSY = 15,
    NHTTP_ERROR_SSL_ROOTCA = 16,
    NHTTP_ERROR_SSL_CLIENTCERT = 17
} NHTTPError;

typedef enum {
    NHTTP_REQMETHOD_GET = 0,
    NHTTP_REQMETHOD_POST = 1,
    NHTTP_REQMETHOD_HEAD = 2,
} NHTTPReqMethod;

typedef void* NHTTPRequestHandle;
typedef void* NHTTPResponseHandle;

typedef void* (*NHTTPAlloc)(size_t size, int align);
typedef void (*NHTTPFree)(void*);
typedef void (*NHTTPReqCallback)(NHTTPError, NHTTPResponseHandle, void*);

int NHTTPStartup(NHTTPAlloc, NHTTPFree, u32);
NHTTPRequestHandle* NHTTPCreateRequest(const char* url, NHTTPReqMethod, char* buffer, size_t bufferSize, NHTTPReqCallback, void*);
int NHTTPSendRequestAsync(NHTTPRequestHandle);

void NHTTPDestroyResponse(NHTTPResponseHandle);
int NHTTPGetResultCode(NHTTPResponseHandle);
int NHTTPGetBodyAll(NHTTPResponseHandle, char**);
//int NHTTPGetHeaderField(NHTTPResponseHandle, const char*, char**);

#ifdef __cplusplus
}
#endif
#endif