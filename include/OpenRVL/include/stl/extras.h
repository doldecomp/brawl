#ifndef MSL_EXTRAS_H
#define MSL_EXTRAS_H
#include <types.h>
#ifdef __cplusplus
extern "C" {
#endif

int stricmp(const char*, const char*);
char* itoa(int value, char* str, int base);

#ifdef __cplusplus
}
#endif
#endif
