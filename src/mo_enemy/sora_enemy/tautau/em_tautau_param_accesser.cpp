#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/tautau/em_tautau_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emTautauParamAccesser g_emTowtowParamAccesser;

emTautauParamAccesser::emTautauParamAccesser()
    : emExtendParamAccesser(Enemy_Towtow) { }

float emTautauParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return static_cast<s32>(ptr->unk4A0);
        case 4001:
            return static_cast<s32>(ptr->unk4A4);
        case 4002:
            return static_cast<s32>(ptr->unk4A8);
        case 4003:
            return static_cast<s32>(ptr->unk4AC);
        default:
            return 0.0f;
    }
}

s32 emTautauParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk434;
        case 24001:
            return ptr->unk438;
        case 24002:
            return ptr->unk488;
        case 24003:
            return ptr->unk48C;
        case 24004:
            return ptr->unk490;
        case 24005:
            return ptr->unk494;
        default:
            return 0;
    }
}

void* emTautauParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk2C0;
        case 44002:
            return &ptr->unk374;
        case 44003:
            return &ptr->unk414;
        case 44004:
            return &ptr->unk424;
        case 44005:
            return &ptr->unk43C;
        case 44006:
            return &ptr->unk44C;
        case 44007:
            return &ptr->unk498;
        default:
            return nullptr;
    }
}

emTautauParamAccesser::~emTautauParamAccesser() { }
