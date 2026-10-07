#include <if/if_mngr.h>
#include <if/if_marth_final.h>
#include <mt/mt_vector.h>
#include <types.h>

extern "C" {

void fn_106_D4E4(Vec3f* dst, const Vec3f* src);
void fn_106_D720(IfMngr* mngr, void* arg);
void fn_106_DA78(IfMngr* mngr, void* arg);
void fn_106_D9DC();
void fn_106_D9E0(u8* obj);
void fn_106_DA94();
void fn_106_DB68();
void fn_106_DB6C();
void fn_106_DB70();
void fn_106_DB74();

void fn_106_D4E4(Vec3f* dst, const Vec3f* src) {
    dst->m_x = src->m_x;
    dst->m_y = src->m_y;
    dst->m_z = src->m_z;
}

void fn_106_D9DC() {}

void fn_106_D9E0(u8* obj) {
    if (obj[136] == 0) {
        fn_106_D720(g_IfMngr, *(void**) (obj + 72));
        obj[136] = 1;
    }
}

void fn_106_DA94() {}

void fn_106_DB68() {}

void fn_106_DB6C() {}

void fn_106_DB70() {}

void fn_106_DB74() {}

}

void IfMarthFinalTask::dispOff(int) {
    if (unk88 == 1) {
        fn_106_DA78(g_IfMngr, unk48);
        unk88 = 0;
    }
}

u32 IfMarthFinalTask::isExecutedCallBack() const {
    return unk84;
}
