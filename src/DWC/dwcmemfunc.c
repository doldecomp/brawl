#include <types.h>
#include <revolution/DWC/dwc_memfunc.h>

extern DWCAlloc lbl_805A0F5C;
extern DWCFree lbl_805A0F58;

typedef struct DWCAllocationHeader {
    u32 magic;
    u32 size;
    u8 reserved[24];
} DWCAllocationHeader;

void DWCi_SetMemFunc(DWCAlloc alloc, DWCFree free) {
    lbl_805A0F5C = alloc;
    lbl_805A0F58 = free;
}

void* DWC_Alloc(int kind, u32 size) {
    DWCAllocationHeader* header = (DWCAllocationHeader*)lbl_805A0F5C(kind, size + 32, 32);
    if (header == NULL) return NULL;
    header->magic = 0x4457434D;
    header->size = size;
    return header + 1;
}

void* DWC_AllocEx(int kind, u32 size, int alignment) {
    DWCAllocationHeader* header = (DWCAllocationHeader*)lbl_805A0F5C(kind, size + 32, alignment);
    if (header == NULL) return NULL;
    header->magic = 0x4457434D;
    header->size = size;
    return header + 1;
}

void DWC_Free(int kind, void* allocation, int size) {
    if (allocation == NULL) return;
    lbl_805A0F58(kind, (DWCAllocationHeader*)allocation - 1, size);
}

extern void fn_8034F028(void* destination, const void* source, u32 size);

void* DWCi_GsMalloc(u32 size) { return DWC_Alloc(9, size); }

void* DWCi_GsRealloc(void* allocation, u32 size) {
    void* replacement = DWC_Alloc(9, size);
    if (replacement == NULL) return NULL;
    if (allocation != NULL) {
        DWCAllocationHeader* header = (DWCAllocationHeader*)allocation - 1;
        u32 previousSize = header->size;
        u32 copySize = size < previousSize ? size : previousSize;
        fn_8034F028(replacement, allocation, copySize);
        DWC_Free(9, allocation, previousSize);
    }
    return replacement;
}

void DWCi_GsFree(void* allocation) { DWC_Free(9, allocation, 0); }
void* DWCi_GsMemalign(int alignment, u32 size) { return DWC_AllocEx(9, size, alignment); }
