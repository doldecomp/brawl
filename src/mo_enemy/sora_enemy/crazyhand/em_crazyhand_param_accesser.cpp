#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/crazyhand/em_crazyhand_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emCrazyhandParamAccesser g_emCrazyHandParamAccesser;

emCrazyhandParamAccesser::emCrazyhandParamAccesser()
    : emExtendParamAccesser(Enemy_Boss_CrazyHand) { }

float emCrazyhandParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk9E0.f;
        case 4001:
            return ptr->unk9E4;
        case 4002:
            return ptr->unk9E8;
        case 4003:
            return ptr->unk9EC;
        case 4004:
            return ptr->unk9F0;
        case 4005:
            return ptr->unk9F4;
        case 4006:
            return ptr->unk9C4;
        case 4007:
            return ptr->unk9C8;
        case 4008:
            return ptr->unk9CC;
        case 4009:
            return ptr->unk9D0;
        case 4010:
            return ptr->unk9DC;
        case 4011:
            return ptr->unk9F8;
        case 4012:
            return ptr->unk9FC;
        default:
            return 0.0f;
    }
}

s32 emCrazyhandParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk9D4;
        case 24001:
            return ptr->unk9D8;
        default:
            return 0;
    }
}

void* emCrazyhandParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk980;
        case 44002:
            return &ptr->unk9A4;
        case 44003:
            return &ptr->unkA00;
        case 44004:
            return &ptr->unkA10;
        case 44005:
            return &ptr->unkA1C;
        case 44006:
            return &ptr->unkA28;
        case 44007:
            return &ptr->unkA34;
        case 44008:
            return &ptr->unkA40;
        case 44009:
            return &ptr->unkA4C;
        case 44010:
            return &ptr->unkA70;
        case 44011:
            return &ptr->unkAA0;
        case 44012:
            return &ptr->unkAD0;
        case 44013:
            return &ptr->unkAF4;
        case 44014:
            return &ptr->unkB24;
        case 44015:
            return &ptr->unkB54;
        case 44016:
            return &ptr->unkBD0;
        default:
            return nullptr;
    }
}

emCrazyhandParamAccesser::~emCrazyhandParamAccesser() { }
