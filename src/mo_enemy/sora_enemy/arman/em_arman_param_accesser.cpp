#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/arman/em_arman_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emArmanParamAccesser g_emArmankParamAccesser;

emArmanParamAccesser::emArmanParamAccesser()
    : emExtendParamAccesser(Enemy_Armank) { }

float emArmanParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0.0f;
}

s32 emArmanParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk834;
        case 24001:
            return ptr->unk838;
        case 24002:
            return ptr->unk844;
        case 24003:
            return ptr->unk848;
        case 24004:
            return ptr->unk84C;
        case 24005:
            return ptr->unk850;
        default:
            return 0;
    }
}

void* emArmanParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk580;
        case 44002:
            return &ptr->unk6C4;
        case 44003:
            return &ptr->unk7E4;
        case 44004:
            return &ptr->unk7EC;
        case 44005:
            return &ptr->unk804;
        case 44006:
            return &ptr->unk81C;
        case 44007:
            return &ptr->unk854;
        case 44008:
            return &ptr->unk83C;
        case 44009:
            return &ptr->unk85C;
        case 44010:
            return &ptr->unk8D8;
        case 44011:
            return &ptr->unk954;
        default:
            return nullptr;
    }
}

emArmanParamAccesser::~emArmanParamAccesser() { }
