#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/kokkon/em_kokkon_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emKokkonParamAccesser g_emPuppitParamAccesser;

emKokkonParamAccesser::emKokkonParamAccesser()
    : emExtendParamAccesser(Enemy_Puppit) { }

float emKokkonParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk344.f;
        case 4001:
            return ptr->unk358;
        case 4002:
            return ptr->unk334;
        case 4003:
            return ptr->unk338;
        default:
            return 0.0f;
    }
}

s32 emKokkonParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0;
}

void* emKokkonParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk280;
        case 44002:
            return &ptr->unk2EC;
        case 44003:
            return &ptr->unk32C;
        case 44004:
            return &ptr->unk33C;
        case 44005:
            return &ptr->unk348;
        case 44006:
            return &ptr->unk35C;
        case 44007:
            return &ptr->unk364;
        case 44008:
            return &ptr->unk36C;
        case 44009:
            return &ptr->unk3E8;
        default:
            return nullptr;
    }
}

emKokkonParamAccesser::~emKokkonParamAccesser() { }
