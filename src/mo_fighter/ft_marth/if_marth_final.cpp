#include <if/if_mngr.h>
#include <mt/mt_vector.h>
#include <types.h>

extern "C" {

void fn_106_D4E4(Vec3f* dst, const Vec3f* src);
void fn_106_D720(IfMngr* mngr, void* arg);
void fn_106_DA78(IfMngr* mngr, void* arg);
void fn_106_D9DC();
void fn_106_D9E0(u8* obj);
void fn_106_DA2C(u8* obj);
void fn_106_DA94();
u8 fn_106_DB60(const u8* obj);
void fn_106_DB68();
void fn_106_DB6C();
void fn_106_DB70();
void fn_106_DB74();

// NONMATCHING: mwcc hoists the three loads ahead of the stores; the target
// interleaves them.
void fn_106_D4E4(Vec3f* dst, const Vec3f* src) {
    dst->m_x = src->m_x;
    dst->m_y = src->m_y;
    dst->m_z = src->m_z;
}

void fn_106_D9DC() {}

// NONMATCHING: mwcc loads the field before dereferencing g_IfMngr; the target
// does the opposite. Hoisting the manager into a local does not move it.
void fn_106_D9E0(u8* obj) {
    if (obj[136] == 0) {
        fn_106_D720(g_IfMngr, *(void**) (obj + 72));
        obj[136] = 1;
    }
}

void fn_106_DA2C(u8* obj) {
    if (obj[136] == 1) {
        fn_106_DA78(g_IfMngr, *(void**) (obj + 72));
        obj[136] = 0;
    }
}

void fn_106_DA94() {}

u8 fn_106_DB60(const u8* obj) {
    return obj[132];
}

void fn_106_DB68() {}

void fn_106_DB6C() {}

void fn_106_DB70() {}

void fn_106_DB74() {}

}
