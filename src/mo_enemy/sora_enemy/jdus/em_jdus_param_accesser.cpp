#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/jdus/em_jdus_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emJdusParamAccesser g_emShaydasParamAccesser;

emJdusParamAccesser::emJdusParamAccesser()
    : emExtendParamAccesser(Enemy_Shaydas) { }

float emJdusParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0.0f;
}

s32 emJdusParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk65C;
        default:
            return 0;
    }
}

void* emJdusParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return &ptr->unk0;
        case 44001:
            return &ptr->unk500;
        case 44002:
            return &ptr->unk5B4;
        case 44003:
            return &ptr->unk634;
        case 44004:
            return &ptr->unk644;
        case 44005:
            return &ptr->unk654;
        case 44006:
            return &ptr->unk660;
        case 44007:
            return &ptr->unk668;
        case 44008:
            return &ptr->unk670;
        case 44009:
            return &ptr->unk688;
        default:
            return nullptr;
    }
}

emJdusParamAccesser::~emJdusParamAccesser() { }
