#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/bombhead/em_bombhead_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emBombheadParamAccesser g_emBombedParamAccesser;

emBombheadParamAccesser::emBombheadParamAccesser()
    : emExtendParamAccesser(Enemy_Bombed) { }

float emBombheadParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk38C;
        case 4001:
            return ptr->unk390;
        case 4002:
            return ptr->unk394;
        default:
            return 0.0f;
    }
}

s32 emBombheadParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk398;
        default:
            return 0;
    }
}

void* emBombheadParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk2C0;
        case 44002:
            return &ptr->unk32C;
        case 44003:
            return &ptr->unk39C;
        case 44004:
            return &ptr->unk418;
        case 44005:
            return &ptr->unk494;
        case 44006:
            return &ptr->unk510;
        default:
            return nullptr;
    }
}

emBombheadParamAccesser::~emBombheadParamAccesser() { }
