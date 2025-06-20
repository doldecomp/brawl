#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/jyakeel/em_jyakeel_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emJyakeelParamAccesser g_emJykParamAccesser;

emJyakeelParamAccesser::emJyakeelParamAccesser()
    : emExtendParamAccesser(Enemy_Jyk) { }

float emJyakeelParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0.0f;
}

s32 emJyakeelParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk264;
        case 24001:
            return ptr->unk268;
        default:
            return 0;
    }
}

void* emJyakeelParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk200;
        case 44002:
            return &ptr->unk224;
        case 44003:
            return &ptr->unk244;
        case 44004:
            return &ptr->unk254;
        default:
            return nullptr;
    }
}

emJyakeelParamAccesser::~emJyakeelParamAccesser() { }
