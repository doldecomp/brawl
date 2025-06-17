#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/robopunch/em_robopunch_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emRobopunchParamAccesser g_emROBSentryParamAccesser;

emRobopunchParamAccesser::emRobopunchParamAccesser()
    : emExtendParamAccesser(Enemy_ROB_Sentry) { }

float emRobopunchParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0.0f;
}

s32 emRobopunchParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0;
}

void* emRobopunchParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk380;
        case 44002:
            return &ptr->unk434;
        case 44003:
            return &ptr->unk4B4;
        case 44004:
            return &ptr->unk4BC;
        case 44005:
            return &ptr->unk4E0;
        case 44006:
            return &ptr->unk4F0;
        default:
            return nullptr;
    }
}

emRobopunchParamAccesser::~emRobopunchParamAccesser() { }
