#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/deathpod/em_deathpod_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emDeathpodParamAccesser g_emRoturretParamAccesser;

emDeathpodParamAccesser::emDeathpodParamAccesser()
    : emExtendParamAccesser(Enemy_Roturret) { }

float emDeathpodParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0.0f;
}

s32 emDeathpodParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk330.b;
        default:
            return 0;
    }
}

void* emDeathpodParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk240;
        case 44002:
            return &ptr->unk2D0;
        case 44003:
            return &ptr->unk310;
        case 44004:
            return &ptr->unk320;
        case 44005:
            return &ptr->unk334;
        case 44006:
            return &ptr->unk344;
        case 44007:
            return &ptr->unk34C;
        case 44008:
            return &ptr->unk354;
        case 44009:
            return &ptr->unk3D0;
        case 44010:
            return &ptr->unk44C;
        case 44011:
            return &ptr->unk4C8;
        case 44012:
            return &ptr->unk544;
        case 44013:
            return &ptr->unk5C0;
        default:
            return nullptr;
    }
}

emDeathpodParamAccesser::~emDeathpodParamAccesser() { }
