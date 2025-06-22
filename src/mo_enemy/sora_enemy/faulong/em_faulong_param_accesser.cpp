#include <em/em_create.h>
#include <em/faulong/em_faulong_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emFaulongParamAccesser g_emTrowlonParamAccesser;

emFaulongParamAccesser::emFaulongParamAccesser()
    : emExtendParamAccesser(Enemy_Trowlon) { }

float emFaulongParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk330.f;
        default:
            return 0.0f;
    }
}

s32 emFaulongParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk32C;
        default:
            return 0;
    }
}

void* emFaulongParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk280;
        case 44002:
            return &ptr->unk2EC;
        default:
            return nullptr;
    }
}

emFaulongParamAccesser::~emFaulongParamAccesser() { }
