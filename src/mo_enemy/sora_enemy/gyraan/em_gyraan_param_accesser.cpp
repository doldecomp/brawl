#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/gyraan/em_gyraan_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emGyraanParamAccesser g_emGreapParamAccesser;

emGyraanParamAccesser::emGyraanParamAccesser()
    : emExtendParamAccesser(Enemy_Greap) { }

float emGyraanParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk510;
        default:
            return 0.0f;
    }
}

s32 emGyraanParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk50C;
        default:
            return 0;
    }
}

void* emGyraanParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk440;
        case 44002:
            return &ptr->unk4AC;
        case 44003:
            return &ptr->unk514;
        case 44004:
            return &ptr->unk51C;
        case 44005:
            return &ptr->unk524;
        case 44006:
            return &ptr->unk52C;
        case 44007:
            return &ptr->unk5A8;
        case 44008:
            return &ptr->unk624;
        default:
            return nullptr;
    }
}

emGyraanParamAccesser::~emGyraanParamAccesser() { }
