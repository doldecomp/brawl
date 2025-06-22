#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/botron/em_botron_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emBotronParamAccesser g_emBuckotParamAccesser;

emBotronParamAccesser::emBotronParamAccesser()
    : emExtendParamAccesser(Enemy_Buckot) { }

float emBotronParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk294.f;
        case 4001:
            return ptr->unk298;
        case 4002:
            return ptr->unk2A0;
        default:
            return 0.0f;
    }
}

s32 emBotronParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk29C;
        case 24001:
            return ptr->unk2A4;
        default:
            return 0;
    }
}

void* emBotronParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk140;
        case 44002:
            return &ptr->unk1F4;
        case 44003:
            return &ptr->unk274;
        case 44004:
            return &ptr->unk284;
        case 44005:
            return &ptr->unk2A8;
        case 44006:
            return &ptr->unk324;
        case 44007:
            return &ptr->unk3A0;
        case 44008:
            return &ptr->unk41C;
        case 44009:
            return &ptr->unk440;
        case 44010:
            return &ptr->unk470;
        case 44011:
            return &ptr->unk4A0;
        case 44012:
            return &ptr->unk4D0;
        case 44013:
            return &ptr->unk500;
        default:
            return nullptr;
    }
}

emBotronParamAccesser::~emBotronParamAccesser() { }
