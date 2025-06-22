#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/pacci/em_pacci_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emPacciParamAccesser g_emFeyeshParamAccesser;

emPacciParamAccesser::emPacciParamAccesser()
    : emExtendParamAccesser(Enemy_Feyesh) { }

float emPacciParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk2C0;
        case 4001:
            return ptr->unk30C;
        case 4002:
            return ptr->unk310;
        default:
            return 0.0f;
    }
}

s32 emPacciParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0;
}

void* emPacciParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk1C0;
        case 44002:
            return &ptr->unk250;
        case 44003:
            return &ptr->unk2B0;
        case 44004:
            return &ptr->unk2C4;
        case 44005:
            return &ptr->unk2E8;
        default:
            return nullptr;
    }
}

emPacciParamAccesser::~emPacciParamAccesser() { }
