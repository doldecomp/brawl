#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/spar/em_spar_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emSparParamAccesser g_emSpaakParamAccesser;

emSparParamAccesser::emSparParamAccesser()
    : emExtendParamAccesser(Enemy_Spaak) { }

float emSparParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk378;
        case 4001:
            return ptr->unk37C.f;
        case 4002:
            return ptr->unk380;
        default:
            return 0.0f;
    }
}

s32 emSparParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk340.i;
        case 24001:
            return ptr->unk374;
        default:
            return 0;
    }
}

void* emSparParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
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
            return &ptr->unk330;
        case 44004:
            return &ptr->unk344;
        case 44005:
            return &ptr->unk354;
        case 44006:
            return &ptr->unk364;
        case 44007:
            return &ptr->unk384;
        case 44008:
            return &ptr->unk400;
        case 44009:
            return &ptr->unk47C;
        case 44010:
            return &ptr->unk4F8;
        default:
            return nullptr;
    }
}

emSparParamAccesser::~emSparParamAccesser() { }
