#include <em/em_extend_param_accesser.h>
#include <so/so_value_accesser.h>
#include <cstring>

static const u32 TableSize = 61;
static bool s_init;
static emExtendParamAccesser* s_accesserTable[TableSize];

emExtendParamAccesser::emExtendParamAccesser(u32 index) {
    if (!s_init) {
        std::memset(s_accesserTable, 0, sizeof(s_accesserTable));
        s_init = true;
    }
    s_accesserTable[index] = this;
}

void emExtendParamAccesser::reset(emExtendParamAccesser* acc, u32 index) {
    s_accesserTable[index] = acc;
}

emExtendParamAccesser* emExtendParamAccesser::getAccesser(u32 index) {
    return s_accesserTable[index];
}

#pragma dont_inline on
emExtendParamAccesser::~emExtendParamAccesser() { }
#pragma dont_inline reset
