#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/flows/em_flows_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emFlowsParamAccesser g_emFloowParamAccesser;

emFlowsParamAccesser::emFlowsParamAccesser()
    : emExtendParamAccesser(Enemy_Floow) { }

float emFlowsParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    return 0.0f;
}

s32 emFlowsParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk35C;
        case 24001:
            return ptr->unk360;
        case 24002:
            return ptr->unk364;
        case 24003:
            return ptr->unk368.i;
        case 24004:
            return ptr->unk36C.i;
        case 24005:
            return ptr->unk370.i;
        case 24006:
            return ptr->unk374;
        default:
            return 0;
    }
}

void* emFlowsParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk200;
        case 44002:
            return &ptr->unk2FC;
        case 44003:
            return &ptr->unk378;
        case 44004:
            return &ptr->unk39C;
        default:
            return nullptr;
    }
}

emFlowsParamAccesser::~emFlowsParamAccesser() { }
