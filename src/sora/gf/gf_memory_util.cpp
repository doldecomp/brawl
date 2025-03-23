#include <mem.h>
#include <gf/gf_memory_util.h>

void gfMemFill(void* dest, u8 value, size_t count) {
    memset(dest, value, count);
}
