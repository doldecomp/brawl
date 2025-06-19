#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/patapata/em_patapata_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emPatapataParamAccesser g_emKoopaParamAccesser;

emPatapataParamAccesser::emPatapataParamAccesser()
    : emExtendParamAccesser(Enemy_Koopa) { }

float emPatapataParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk694;
        case 4001:
            return ptr->unk698;
        case 4002:
            return ptr->unk6B0;
        case 4003:
            return ptr->unk69C;
        case 4004:
            return ptr->unk6B4;
        default:
            return 0.0f;
    }
}

s32 emPatapataParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0;
}

void* emPatapataParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk580;
        case 44002:
            return &ptr->unk634;
        case 44003:
            return &ptr->unk6A0;
        case 44004:
            return &ptr->unk6A8;
        case 44005:
            return &ptr->unk6B8;
        case 44006:
            return &ptr->unk6E0;
        default:
            return nullptr;
    }
}

emPatapataParamAccesser::~emPatapataParamAccesser() { }
