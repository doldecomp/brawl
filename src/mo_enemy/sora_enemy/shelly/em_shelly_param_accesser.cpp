#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/shelly/em_shelly_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emShellyParamAccesser g_emShellpodParamAccesser;

emShellyParamAccesser::emShellyParamAccesser()
    : emExtendParamAccesser(Enemy_Shellpod) { }

float emShellyParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk2A8;
        case 4001:
            return ptr->unk2AC;
        default:
            return 0.0f;
    }
}

s32 emShellyParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0;
}

void* emShellyParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk200;
        case 44002:
            return &ptr->unk248;
        case 44003:
            return &ptr->unk288;
        case 44004:
            return &ptr->unk298;
        default:
            return nullptr;
    }
}

emShellyParamAccesser::~emShellyParamAccesser() { }
