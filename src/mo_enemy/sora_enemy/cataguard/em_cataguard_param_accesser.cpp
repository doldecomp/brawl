#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/cataguard/em_cataguard_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emCataguardParamAccesser g_emAutolanceParamAccesser;

emCataguardParamAccesser::emCataguardParamAccesser()
    : emExtendParamAccesser(Enemy_Autolance) { }

float emCataguardParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk510;
        case 4001:
            return ptr->unk53C;
        case 4002:
            return ptr->unk544;
        case 4003:
            return ptr->unk548;
        case 4004:
            return ptr->unk54C;
        default:
            return 0.0f;
    }
}

s32 emCataguardParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk540;
        default:
            return 0;
    }
}

void* emCataguardParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk380;
        case 44002:
            return &ptr->unk458;
        case 44003:
            return &ptr->unk4F8;
        case 44004:
            return &ptr->unk514;
        case 44005:
            return &ptr->unk51C;
        case 44006:
            return &ptr->unk524;
        case 44007:
            return &ptr->unk52C;
        case 44008:
            return &ptr->unk534;
        case 44009:
            return &ptr->unk550;
        case 44010:
            return &ptr->unk5CC;
        case 44011:
            return &ptr->unk648;
        case 44012:
            return &ptr->unk6C4;
        case 44013:
            return &ptr->unk740;
        case 44014:
            return &ptr->unk7BC;
        default:
            return nullptr;
    }
}

emCataguardParamAccesser::~emCataguardParamAccesser() { }
