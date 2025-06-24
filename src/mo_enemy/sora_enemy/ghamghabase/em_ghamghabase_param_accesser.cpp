#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/ghamghabase/em_ghamghabase_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emGhamghabaseParamAccesser g_emGamygaBaseParamAccesser;

emGhamghabaseParamAccesser::emGhamghabaseParamAccesser()
    : emExtendParamAccesser(Enemy_GamygaBase) {

    emExtendParamAccesser::reset(this, 48);
    emExtendParamAccesser::reset(this, 49);
    emExtendParamAccesser::reset(this, 50);
}

float emGhamghabaseParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk1C4;
        case 4001:
            return ptr->unk1C8;
        default:
            return 0.0f;
    }
}

s32 emGhamghabaseParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0;
}

void* emGhamghabaseParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk180;
        case 44002:
            return &ptr->unk1A4;
        case 44003:
            return &ptr->unk1CC;
        default:
            return nullptr;
    }
}

emGhamghabaseParamAccesser::~emGhamghabaseParamAccesser() { }
