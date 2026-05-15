#include <cstring>
#include <ft/ft_extend_param_accesser.h>
#include <ft/ft_entry.h>
#include <revolution/OS/OSError.h>
#include <types.h>

static bool g_ftExtendParamAccesserTableInit;
static ftExtendParamAccesser* g_ftExtendParamAccesserTable[Fighter_Count];

ftExtendParamAccesser::ftExtendParamAccesser(ftKind kind) {
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

ftExtendParamAccesser* ftExtendParamAccesser::getAccesser(ftKind kind) {
    return g_ftExtendParamAccesserTable[kind];
}

bool ftExtendParamAccesser::isExistAccesser(ftKind kind) {
    if (!g_ftExtendParamAccesserTable[kind])
        OSReport("_Accessers[ %d ] == NULL \n", kind);
    if (!g_ftExtendParamAccesserTableInit)
        OSReport("_InitializeAccessers == false \n");
    return (g_ftExtendParamAccesserTable[kind] && g_ftExtendParamAccesserTableInit);
}
