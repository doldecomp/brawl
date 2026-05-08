#include <ft/ft_class_info.h>
#include <gm/gm_lib.h>
#include <so/so_null.h>
#include <types.h>

static ftClassInfo* g_ftClassInfoTable[Fighters::Count];
static bool g_ftClassInfoTableInit;
ftClassInfoNull g_ftClassInfoNull;

ftClassInfo::ftClassInfo(bool isNull) : soNullable(isNull) {
    if (!g_ftClassInfoTableInit) {
        g_ftClassInfoTableInit = true;
        for (u32 i = 0; i < Fighters::Count; i++)
            g_ftClassInfoTable[i] = &g_ftClassInfoNull;
    }
}

ftClassInfo::~ftClassInfo() { }

ftClassInfo* ftClassInfo::getClassInfo(Fighters::ftFighterKind kind) {
    return g_ftClassInfoTable[kind];
}

void ftClassInfo::setClassInfo(Fighters::ftFighterKind kind, ftClassInfo* info) {
    g_ftClassInfoTable[kind] = info;
}

ftClassInfo* ftClassInfoNull::create() const {
    return nullptr;
}

ftClassInfoNull::~ftClassInfoNull() { }
