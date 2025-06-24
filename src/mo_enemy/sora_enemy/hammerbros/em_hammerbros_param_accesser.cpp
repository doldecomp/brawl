#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/hammerbros/em_hammerbros_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emHammerbrosParamAccesser g_emHammerBroParamAccesser;

emHammerbrosParamAccesser::emHammerbrosParamAccesser()
    : emExtendParamAccesser(Enemy_HammerBro) { }

float emHammerbrosParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk278;
        default:
            return 0.0f;
    }
}

s32 emHammerbrosParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk27C;
        default:
            return 0;
    }
}

void* emHammerbrosParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk1C0;
        case 44002:
            return &ptr->unk208;
        case 44003:
            return &ptr->unk248;
        case 44004:
            return &ptr->unk258;
        case 44005:
            return &ptr->unk268;
        case 44006:
            return &ptr->unk280;
        default:
            return nullptr;
    }
}

emHammerbrosParamAccesser::~emHammerbrosParamAccesser() { }
