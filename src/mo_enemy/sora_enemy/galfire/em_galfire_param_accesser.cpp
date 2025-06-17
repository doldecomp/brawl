#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/galfire/em_galfire_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emGalfireParamAccesser g_emGlireParamAccesser;

emGalfireParamAccesser::emGalfireParamAccesser()
    : emExtendParamAccesser(Enemy_Glire) {

    emExtendParamAccesser::reset(this, 44);
    emExtendParamAccesser::reset(this, 45);
}

float emGalfireParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk28C;
        case 4001:
            return ptr->unk290;
        case 4002:
            return ptr->unk298;
        default:
            return 0.0f;
    }
}

s32 emGalfireParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk294;
        case 24001:
            return ptr->unk295;
        default:
            return 0;
    }
}

void* emGalfireParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk240;
        case 44002:
            return &ptr->unk264;
        case 44003:
            return &ptr->unk284;
        default:
            return nullptr;
    }
}

emGalfireParamAccesser::~emGalfireParamAccesser() { }
