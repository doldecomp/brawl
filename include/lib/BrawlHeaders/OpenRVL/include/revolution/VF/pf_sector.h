#ifndef RVL_SDK_VF_PF_SECTOR_H
#define RVL_SDK_VF_PF_SECTOR_H
#include <revolution/types.h>
#ifdef __cplusplus
extern "C" {
#endif

#include <revolution/VF/pf.h>

int PFSEC_ReadData(void* cache, void* buffer, int sector, int offset, int len, int* success, int unk);
int PFSEC_WriteData(void* cache, void* buffer, int sector, int offset, int len, int* success, int unk);

#ifdef __cplusplus
}
#endif
#endif