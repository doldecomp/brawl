#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/ghamgha/em_ghamgha_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emGhamghaParamAccesser g_emGamygaParamAccesser;

emGhamghaParamAccesser::emGhamghaParamAccesser()
    : emExtendParamAccesser(Enemy_Gamyga) { }

float emGhamghaParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk104;
        case 4001:
            return ptr->unk108;
        case 4002:
            return ptr->unk10C;
        default:
            return 0.0f;
    }
}

s32 emGhamghaParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0;
}

void* emGhamghaParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unkC0;
        case 44002:
            return &ptr->unkE4;
        case 44003:
            return &ptr->unk110;
        case 44004:
            return &ptr->unk120;
        case 44005:
            return &ptr->unk130;
        case 44006:
            return &ptr->unk1AC;
        default:
            return nullptr;
    }
}

emGhamghaParamAccesser::~emGhamghaParamAccesser() { }
