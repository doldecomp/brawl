#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/robodistance/em_robodistance_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emRobodistanceParamAccesser g_emROBDistanceParamAccesser;

emRobodistanceParamAccesser::emRobodistanceParamAccesser()
    : emExtendParamAccesser(Enemy_ROB_Distance) { }

float emRobodistanceParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0.0f;
}

s32 emRobodistanceParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0;
}

void* emRobodistanceParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk180;
        case 44002:
            return &ptr->unk258;
        case 44003:
            return &ptr->unk2F8;
        case 44004:
            return &ptr->unk300;
        case 44005:
            return &ptr->unk308;
        default:
            return nullptr;
    }
}

emRobodistanceParamAccesser::~emRobodistanceParamAccesser() { }
