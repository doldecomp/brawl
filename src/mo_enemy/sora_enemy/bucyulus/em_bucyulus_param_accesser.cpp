#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/bucyulus/em_bucyulus_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emBucyulusParamAccesser g_emBucculusParamAccesser;

emBucyulusParamAccesser::emBucyulusParamAccesser()
    : emExtendParamAccesser(Enemy_Bucculus) { }

float emBucyulusParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk344.f;
        case 4001:
            return ptr->unk348;
        case 4002:
            return ptr->unk34C;
        case 4003:
            return ptr->unk350;
        case 4004:
            return ptr->unk354;
        case 4005:
            return ptr->unk368.f;
        case 4006:
            return ptr->unk36C.f;
        case 4007:
            return ptr->unk370.f;
        default:
            return 0.0f;
    }
}

s32 emBucyulusParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0;
}

void* emBucyulusParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
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
            return &ptr->unk358;
        default:
            return nullptr;
    }
}

emBucyulusParamAccesser::~emBucyulusParamAccesser() { }
