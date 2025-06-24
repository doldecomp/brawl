#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/mite/em_mite_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emMiteParamAccesser g_emMiteParamAccesser;

emMiteParamAccesser::emMiteParamAccesser()
    : emExtendParamAccesser(Enemy_Mite) { }

float emMiteParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unkA40;
        case 4001:
            return ptr->unkA44;
        case 4002:
            return ptr->unkA48;
        default:
            return 0.0f;
    }
}

s32 emMiteParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unkA4C;
        default:
            return 0;
    }
}

void* emMiteParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk700;
        case 44002:
            return &ptr->unk7FC;
        case 44003:
            return &ptr->unk8DC;
        case 44004:
            return &ptr->unk90C;
        case 44005:
            return &ptr->unk93C;
        case 44006:
            return &ptr->unk96C;
        case 44007:
            return &ptr->unk978;
        case 44008:
            return &ptr->unk99C;
        case 44009:
            return &ptr->unk9CC;
        case 44010:
            return &ptr->unk9E4;
        case 44011:
            return &ptr->unk9FC;
        case 44012:
            return &ptr->unkA0C;
        case 44013:
            return &ptr->unkA30;
        case 44014:
            return &ptr->unkA38;
        default:
            return nullptr;
    }
}

emMiteParamAccesser::~emMiteParamAccesser() { }
