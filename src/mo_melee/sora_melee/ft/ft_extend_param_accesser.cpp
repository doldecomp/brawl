#include <cstring>
#include <ft/ft_extend_param_accesser.h>
#include <gm/gm_lib.h>
#include <revolution/OS/OSError.h>
#include <types.h>

static bool g_ftExtendParamAccesserTableInit;
static ftExtendParamAccesser* g_ftExtendParamAccesserTable[Fighters::Count];

ftExtendParamAccesser::ftExtendParamAccesser(Fighters::ftFighterKind kind) {
    if (!g_ftExtendParamAccesserTableInit) {
        std::memset(g_ftExtendParamAccesserTable, 0, sizeof(g_ftExtendParamAccesserTable));
        g_ftExtendParamAccesserTableInit = true;
    }
    g_ftExtendParamAccesserTable[kind] = this;
    m_kind = kind;
}

ftExtendParamAccesser::~ftExtendParamAccesser() {
    g_ftExtendParamAccesserTable[m_kind] = 0;
}

ftExtendParamAccesser* ftExtendParamAccesser::getAccesser(Fighters::ftFighterKind kind) {
    return g_ftExtendParamAccesserTable[kind];
}

bool ftExtendParamAccesser::isExistAccesser(Fighters::ftFighterKind kind) {
    if (!g_ftExtendParamAccesserTable[kind])
        OSReport("_Accessers[ %d ] == NULL \n", kind);
    if (!g_ftExtendParamAccesserTableInit)
        OSReport("_InitializeAccessers == false \n");
    return (g_ftExtendParamAccesserTable[kind] && g_ftExtendParamAccesserTableInit);
}
