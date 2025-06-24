#include <em/em_create.h>
#include <em/falconflyer/em_falconflyer_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emFalconflyerParamAccesser g_emFalconFlyerParamAccesser;

emFalconflyerParamAccesser::emFalconflyerParamAccesser()
    : emExtendParamAccesser(Enemy_Boss_FalconFlyer) { }

float emFalconflyerParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0.0f;
}

s32 emFalconflyerParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk344.i;
        default:
            return 0;
    }
}

void* emFalconflyerParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk300;
        case 44002:
            return &ptr->unk324;
        case 44003:
            return &ptr->unk348;
        default:
            return nullptr;
    }
}

emFalconflyerParamAccesser::~emFalconflyerParamAccesser() { }
