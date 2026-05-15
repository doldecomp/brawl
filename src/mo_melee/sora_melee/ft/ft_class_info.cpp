#include <ft/ft_class_info.h>
#include <ft/ft_entry.h>
#include <so/so_null.h>
#include <types.h>

static ftClassInfo* g_ftClassInfoTable[Fighter_Count];
static bool g_ftClassInfoTableInit;
ftClassInfoNull g_ftClassInfoNull;

ftClassInfo::ftClassInfo(bool isNull) : soNullable(isNull) {
    if (!g_ftClassInfoTableInit) {
        g_ftClassInfoTableInit = true;
        for (u32 i = 0; i < Fighter_Count; i++)
            g_ftClassInfoTable[i] = &g_ftClassInfoNull;
    }
}

ftClassInfo::~ftClassInfo() { }

ftClassInfo* ftClassInfo::getClassInfo(ftKind kind) {
    return g_ftClassInfoTable[kind];
}

void ftClassInfo::setClassInfo(ftKind kind, ftClassInfo* info) {
    g_ftClassInfoTable[kind] = info;
}

ftClassInfo* ftClassInfoNull::create() const {
    return nullptr;
}

ftClassInfoNull::~ftClassInfoNull() { }
