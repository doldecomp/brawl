#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/ridley/em_ridley_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emRidleyParamAccesser g_emRidleyParamAccesser;

emRidleyParamAccesser::emRidleyParamAccesser()
    : emExtendParamAccesser(Enemy_Boss_Ridley) { }

float emRidleyParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk5C8.f;
        case 4001:
            return ptr->unk5CC.f;
        default:
            return 0.0f;
    }
}

s32 emRidleyParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk5B4;
        case 24001:
            return ptr->unk5B8;
        case 24002:
            return ptr->unk5BC;
        case 24003:
            return ptr->unk5C0;
        case 24004:
            return ptr->unk5C4;
        default:
            return 0;
    }
}

void* emRidleyParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk4C0;
        case 44002:
            return &ptr->unk574;
        case 44003:
            return &ptr->unk5D0;
        case 44004:
            return &ptr->unk5D8;
        case 44005:
            return &ptr->unk678;
        case 44006:
            return &ptr->unk684;
        case 44007:
            return &ptr->unk690;
        case 44008:
            return &ptr->unk69C;
        case 44009:
            return &ptr->unk5E8;
        case 44010:
            return &ptr->unk600;
        case 44011:
            return &ptr->unk624;
        case 44012:
            return &ptr->unk63C;
        case 44013:
            return &ptr->unk654;
        default:
            return nullptr;
    }
}

emRidleyParamAccesser::~emRidleyParamAccesser() { }
