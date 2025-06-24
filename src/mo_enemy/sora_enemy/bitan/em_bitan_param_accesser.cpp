#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/bitan/em_bitan_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emBitanParamAccesser g_emBytanParamAccesser;

emBitanParamAccesser::emBitanParamAccesser()
    : emExtendParamAccesser(Enemy_Bytan) { }

float emBitanParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk7E4;
        case 4001:
            return ptr->unk818;
        case 4002:
            return ptr->unk8C0;
        default:
            return 0.0f;
    }
}

s32 emBitanParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk7E0;
        default:
            return 0;
    }
}

void* emBitanParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk740;
        case 44002:
            return &ptr->unk788;
        case 44003:
            return &ptr->unk7C8;
        case 44004:
            return &ptr->unk7D0;
        case 44005:
            return &ptr->unk7E8;
        case 44006:
            return &ptr->unk7F8;
        case 44007:
            return &ptr->unk808;
        case 44008:
            return &ptr->unk824;
        case 44009:
            return &ptr->unk81C;
        case 44010:
            return &ptr->unk860;
        default:
            return nullptr;
    }
}

emBitanParamAccesser::~emBitanParamAccesser() { }
