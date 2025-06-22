#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/aroaros/em_aroaros_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emAroarosParamAccesser g_emAurorosParamAccesser;

emAroarosParamAccesser::emAroarosParamAccesser()
    : emExtendParamAccesser(Enemy_Auroros) { }

float emAroarosParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk33C;
        case 4001:
            return ptr->unk340.f;
        default:
            return 0.0f;
    }
}

s32 emAroarosParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0;
}

void* emAroarosParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk280;
        case 44002:
            return &ptr->unk2EC;
        case 44003:
            return &ptr->unk32C;
        case 44004:
            return &ptr->unk334;
        case 44005:
            return &ptr->unk344;
        default:
            return nullptr;
    }
}

emAroarosParamAccesser::~emAroarosParamAccesser() { }
