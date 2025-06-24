#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/masterhand/em_masterhand_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emMasterhandParamAccesser g_emMasterHandParamAccesser;

emMasterhandParamAccesser::emMasterhandParamAccesser()
    : emExtendParamAccesser(Enemy_Boss_MasterHand) { }

float emMasterhandParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unkBA4;
        case 4001:
            return ptr->unkBA8;
        case 4002:
            return ptr->unkBAC;
        case 4003:
            return ptr->unkBB0;
        case 4004:
            return ptr->unkBB4;
        case 4005:
            return ptr->unkBB8;
        case 4006:
            return ptr->unkBBC;
        case 4007:
            return ptr->unkBC0;
        case 4008:
            return ptr->unkBC4;
        case 4009:
            return ptr->unkBC8;
        case 4010:
            return ptr->unkBCC;
        case 4011:
            return ptr->unkBD0;
        case 4012:
            return ptr->unkBD4;
        case 4013:
            return ptr->unkBD8;
        default:
            return 0.0f;
    }
}

s32 emMasterhandParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unkB88;
        case 24001:
            return ptr->unkB8C;
        case 24002:
            return ptr->unkB90;
        case 24003:
            return ptr->unkB94;
        case 24004:
            return ptr->unkB98;
        case 24005:
            return ptr->unkB9C;
        case 24006:
            return ptr->unkBA0;
        default:
            return 0;
    }
}

void* emMasterhandParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unkB00;
        case 44002:
            return &ptr->unkB48;
        case 44003:
            return &ptr->unkBDC;
        case 44004:
            return &ptr->unkBEC;
        case 44005:
            return &ptr->unkBF8;
        case 44006:
            return &ptr->unkC04;
        case 44007:
            return &ptr->unkC10;
        case 44008:
            return &ptr->unkC1C;
        case 44009:
            return &ptr->unkC40;
        case 44010:
            return &ptr->unkC64;
        case 44011:
            return &ptr->unkC88;
        case 44012:
            return &ptr->unkCAC;
        case 44013:
            return &ptr->unkCC4;
        default:
            return nullptr;
    }
}

emMasterhandParamAccesser::~emMasterhandParamAccesser() { }
