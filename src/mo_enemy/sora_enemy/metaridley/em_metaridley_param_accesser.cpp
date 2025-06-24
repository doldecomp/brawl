#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/metaridley/em_metaridley_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emMetaridleyParamAccesser g_emMetaRidleyParamAccesser;

emMetaridleyParamAccesser::emMetaridleyParamAccesser()
    : emExtendParamAccesser(Enemy_Boss_MetaRidley) { }

float emMetaridleyParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk5D8;
        case 4001:
            return ptr->unk5DC;
        case 4002:
            return ptr->unk5E0;
        case 4003:
            return ptr->unk5E4;
        case 4004:
            return ptr->unk5E8;
        case 4005:
            return ptr->unk5EC;
        case 4006:
            return ptr->unk5F0;
        default:
            return 0.0f;
    }
}

s32 emMetaridleyParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk5C8.i;
        case 24001:
            return ptr->unk5CC.i;
        case 24002:
            return ptr->unk5D0;
        case 24003:
            return ptr->unk5D4;
        default:
            return 0;
    }
}

void* emMetaridleyParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk540;
        case 44002:
            return &ptr->unk588;
        case 44003:
            return &ptr->unk5F4;
        case 44004:
            return &ptr->unk5FC;
        case 44005:
            return &ptr->unk60C;
        case 44006:
            return &ptr->unk618;
        case 44007:
            return &ptr->unk624;
        case 44008:
            return &ptr->unk630;
        case 44009:
            return &ptr->unk63C;
        case 44010:
            return &ptr->unk654;
        case 44011:
            return &ptr->unk66C;
        case 44012:
            return &ptr->unk684;
        case 44013:
            return &ptr->unk69C;
        case 44014:
            return &ptr->unk718;
        case 44015:
            return &ptr->unk794;
        case 44016:
            return &ptr->unk810;
        default:
            return nullptr;
    }
}

emMetaridleyParamAccesser::~emMetaridleyParamAccesser() { }
