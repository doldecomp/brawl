#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/teckin/em_teckin_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emTeckinParamAccesser g_emTickenParamAccesser;

emTeckinParamAccesser::emTeckinParamAccesser()
    : emExtendParamAccesser(Enemy_Ticken) { }

float emTeckinParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0.0f;
}

s32 emTeckinParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk52C;
        default:
            return 0;
    }
}

void* emTeckinParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk440;
        case 44002:
            return &ptr->unk4AC;
        case 44003:
            return &ptr->unk50C;
        case 44004:
            return &ptr->unk51C;
        default:
            return nullptr;
    }
}

emTeckinParamAccesser::~emTeckinParamAccesser() { }
