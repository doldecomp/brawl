#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/popperam/em_popperam_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emPopperamParamAccesser g_emPoppantParamAccesser;

emPopperamParamAccesser::emPopperamParamAccesser()
    : emExtendParamAccesser(Enemy_Poppant) { }

float emPopperamParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk4C4.f;
        case 4001:
            return ptr->unk4C8.f;
        case 4002:
            return ptr->unk4CC.f;
        case 4003:
            return ptr->unk4D0;
        case 4004:
            return ptr->unk4D4;
        case 4005:
            return ptr->unk4D8;
        default:
            return 0.0f;
    }
}

s32 emPopperamParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk4DC;
        default:
            return 0;
    }
}

void* emPopperamParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk3C0;
        case 44002:
            return &ptr->unk42C;
        case 44003:
            return &ptr->unk48C;
        case 44004:
            return &ptr->unk49C;
        case 44005:
            return &ptr->unk4AC;
        case 44006:
            return &ptr->unk550;
        case 44007:
            return &ptr->unk5CC;
        case 44008:
            return &ptr->unk4E0;
        case 44009:
            return &ptr->unk4F0;
        case 44010:
            return &ptr->unk648;
        case 44011:
            return &ptr->unk670;
        case 44012:
            return &ptr->unk698;
        case 44013:
            return &ptr->unk6C0;
        case 44014:
            return &ptr->unk6E8;
        case 44015:
            return &ptr->unk710;
        default:
            return nullptr;
    }
}

emPopperamParamAccesser::~emPopperamParamAccesser() { }
