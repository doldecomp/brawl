#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/cymal/em_cymal_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emCymalParamAccesser g_emCymulParamAccesser;

emCymalParamAccesser::emCymalParamAccesser()
    : emExtendParamAccesser(Enemy_Cymul) { }

float emCymalParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0.0f;
}

s32 emCymalParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0;
}

void* emCymalParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk280;
        case 44002:
            return &ptr->unk2C8;
        case 44003:
            return &ptr->unk2E8;
        case 44004:
            return &ptr->unk2F0;
        default:
            return nullptr;
    }
}

emCymalParamAccesser::~emCymalParamAccesser() { }
