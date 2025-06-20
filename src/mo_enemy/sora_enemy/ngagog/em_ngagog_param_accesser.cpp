#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/ngagog/em_ngagog_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emNgagogParamAccesser g_emNagagogParamAccesser;

emNgagogParamAccesser::emNgagogParamAccesser()
    : emExtendParamAccesser(Enemy_Nagagog) { }

float emNgagogParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk9F4;
        case 4001:
            return ptr->unk9F8;
        case 4002:
            return ptr->unk9FC;
        case 4003:
            return ptr->unkA00;
        case 4004:
            return ptr->unkA04;
        case 4005:
            return ptr->unkA08;
        case 4006:
            return ptr->unkA0C;
        case 4007:
            return ptr->unk9CC;
        default:
            return 0.0f;
    }
}

s32 emNgagogParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk9E0;
        default:
            return 0;
    }
}

void* emNgagogParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk900;
        case 44002:
            return &ptr->unk96C;
        case 44003:
            return &ptr->unk9D0;
        case 44004:
            return &ptr->unk9E4;
        case 44005:
            return &ptr->unkA10;
        case 44006:
            return &ptr->unkA34;
        case 44007:
            return &ptr->unkA64;
        case 44008:
            return &ptr->unkAA0;
        default:
            return nullptr;
    }
}

emNgagogParamAccesser::~emNgagogParamAccesser() { }
