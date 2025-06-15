#include <em/em_create.h>
#include <em/killer/em_killer_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emKillerParamAccesser g_emBulletBillParamAccesser;

emKillerParamAccesser::emKillerParamAccesser()
    : emExtendParamAccesser(Enemy_BulletBill) { }

float emKillerParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk2F4;
        case 4001:
            return ptr->unk2F8;
        default:
            return 0.0f;
    }
}

s32 emKillerParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk2EC;
        case 24001:
            return ptr->unk2F0;
        default:
            return 0;
    }
}

void* emKillerParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk240;
        case 44002:
            return &ptr->unk2AC;
        default:
            return nullptr;
    }
}

emKillerParamAccesser::~emKillerParamAccesser() { }
