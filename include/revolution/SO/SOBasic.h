#ifndef RVL_SDK_SO_BASIC_H
#define RVL_SDK_SO_BASIC_H

#include <revolution/types.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void* (*alloc_t)(int, size_t);
typedef void (*free_t)(int, void*);
typedef struct SOInitInfo {
    alloc_t allocator;
    free_t dealloc;
} SOInitInfo;

void SOFree(int, void*);
void* SOAlloc(int, size_t);

int SOInit(SOInitInfo* info);
int SOStartupEx(u32);
int SOSocket(int domain, int type, int protocal);
int SOBind(int socket, const struct sockaddr* address, int address_len);
int SOConnect(int socket, const struct sockaddr* address, int address_len);
int SOClose(int socket);
u32 SORecvFrom(int socket, void* buffer, u32 length, int flags, struct sockaddr* address, u32* address_len);
u32 SOSendTo(int socket, const void* message, u32 length, int flags, const struct sockaddr* dest_addr, u32 dest_len);
int SOCleanup(void);
int SOFinish(void);

char* SOInetNtoA(struct in_addr in);
u32 SOHtoNl(u32 hostlong);
u32 SOHtoNs(u32 hostshort);
u32 SOHtoHl(u32 netlong);
u32 SOHtoHs(u32 netshort);
u32 SONtoHs(short);

#ifdef __cplusplus
}
#endif
#endif
