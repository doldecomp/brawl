#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/siralamos/em_siralamos_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emSiralamosParamAccesser g_emArmightParamAccesser;

emSiralamosParamAccesser::emSiralamosParamAccesser()
    : emExtendParamAccesser(Enemy_Armight) { }

float emSiralamosParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0.0f;
}

s32 emSiralamosParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk4C4.i;
        case 24001:
            return ptr->unk4C8.i;
        case 24002:
            return ptr->unk4CC.i;
        default:
            return 0;
    }
}

void* emSiralamosParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk2C0;
        case 44002:
            return &ptr->unk404;
        case 44003:
            return &ptr->unk4D0;
        case 44004:
            return &ptr->unk4E8;
        case 44005:
            return &ptr->unk500;
        case 44006:
            return &ptr->unk518;
        case 44007:
            return &ptr->unk594;
        case 44008:
            return &ptr->unk610;
        case 44009:
            return &ptr->unk68C;
        default:
            return nullptr;
    }
}

emSiralamosParamAccesser::~emSiralamosParamAccesser() { }
