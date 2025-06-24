#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/dekakuribo/em_dekakuribo_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emDekakuriboParamAccesser g_emGiantGoombaParamAccesser;

emDekakuriboParamAccesser::emDekakuriboParamAccesser()
    : emExtendParamAccesser(Enemy_GiantGoomba) { }

float emDekakuriboParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk388;
        case 4001:
            return ptr->unk388;
        case 4002:
            return ptr->unk390;
        case 4003:
            return ptr->unk394;
        case 4004:
            return ptr->unk398.f;
        default:
            return 0.0f;
    }
}

s32 emDekakuriboParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0;
}

void* emDekakuriboParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk280;
        case 44002:
            return &ptr->unk310;
        case 44003:
            return &ptr->unk370;
        case 44004:
            return &ptr->unk378;
        default:
            return nullptr;
    }
}

emDekakuriboParamAccesser::~emDekakuriboParamAccesser() { }
