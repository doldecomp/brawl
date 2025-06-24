#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/robohoming/em_robohoming_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emRobohomingParamAccesser g_emROBLauncherParamAccesser;

emRobohomingParamAccesser::emRobohomingParamAccesser()
    : emExtendParamAccesser(Enemy_ROB_Launcher) { }

float emRobohomingParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0.0f;
}

s32 emRobohomingParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0;
}

void* emRobohomingParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return &ptr->unk0;
        case 44001:
            return &ptr->unk140;
        case 44002:
            return &ptr->unk188;
        case 44003:
            return &ptr->unk1A8;
        case 44004:
            return &ptr->unk1B0;
        case 44005:
            return &ptr->unk22C;
        default:
            return nullptr;
    }
}

emRobohomingParamAccesser::~emRobohomingParamAccesser() { }
