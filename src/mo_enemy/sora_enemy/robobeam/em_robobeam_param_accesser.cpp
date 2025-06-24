#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/robobeam/em_robobeam_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emRobobeamParamAccesser g_emROBBlasterParamAccesser;

emRobobeamParamAccesser::emRobobeamParamAccesser()
    : emExtendParamAccesser(Enemy_ROB_Blaster) { }

float emRobobeamParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0.0f;
}

s32 emRobobeamParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk1B0;
        case 24001:
            return ptr->unk1B4;
        default:
            return 0;
    }
}

void* emRobobeamParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk140;
        case 44002:
            return &ptr->unk188;
        case 44003:
            return &ptr->unk1A8;
        case 44004:
            return &ptr->unk1B8;
        case 44005:
            return &ptr->unk234;
        case 44006:
            return &ptr->unk2B0;
        default:
            return nullptr;
    }
}

emRobobeamParamAccesser::~emRobobeamParamAccesser() { }
