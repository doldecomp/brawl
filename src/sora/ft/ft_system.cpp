#include <ft/ft_system.h>
#include <types.h>

ftSystem g_ftSystem;

ftSystem::~ftSystem() { }

void ftSystem::setCommonResourceData(u32 p1, u32 p2) {
    unk0 = p1;
    unk4 = p2;
}
