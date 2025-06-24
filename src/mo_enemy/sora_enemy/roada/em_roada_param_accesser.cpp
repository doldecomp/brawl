#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/roada/em_roada_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emRoadaParamAccesser g_emRoaderParamAccesser;

emRoadaParamAccesser::emRoadaParamAccesser()
    : emExtendParamAccesser(Enemy_Roader) { }

float emRoadaParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0.0f;
}

s32 emRoadaParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk64C;
        case 24001:
            return ptr->unk650;
        case 24002:
            return ptr->unk65C;
        case 24003:
            return ptr->unk660;
        default:
            return 0;
    }
}

void* emRoadaParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk580;
        case 44002:
            return &ptr->unk5EC;
        case 44003:
            return &ptr->unk654;
        case 44004:
            return &ptr->unk664;
        case 44005:
            return &ptr->unk66C;
        case 44006:
            return &ptr->unk674;
        default:
            return nullptr;
    }
}

emRoadaParamAccesser::~emRoadaParamAccesser() { }
