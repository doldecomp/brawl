#include <em/em_create.h>
#include <em/boobas/em_boobas_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emBoobasParamAccesser g_emBorborasParamAccesser;

emBoobasParamAccesser::emBoobasParamAccesser()
    : emExtendParamAccesser(Enemy_Borboras) { }

float emBoobasParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0.0f;
}

s32 emBoobasParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk4FC;
        case 24001:
            return ptr->unk500;
        case 24002:
            return ptr->unk504;
        default:
            return 0;
    }
}

void* emBoobasParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk380;
        case 44002:
            return &ptr->unk47C;
        case 44003:
            return &ptr->unk508;
        default:
            return nullptr;
    }
}

emBoobasParamAccesser::~emBoobasParamAccesser() { }
