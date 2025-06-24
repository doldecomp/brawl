#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/rayquaza/em_rayquaza_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emRayquazaParamAccesser g_emRayquazaParamAccesser;

emRayquazaParamAccesser::emRayquazaParamAccesser()
    : emExtendParamAccesser(Enemy_Boss_Rayquaza) { }

float emRayquazaParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk354;
        case 4001:
            return ptr->unk358;
        case 4002:
            return ptr->unk344.f;
        case 4003:
            return ptr->unk348;
        case 4004:
            return ptr->unk350;
        default:
            return 0.0f;
    }
}

s32 emRayquazaParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk34C.i;
        default:
            return 0;
    }
}

void* emRayquazaParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk300;
        case 44002:
            return &ptr->unk324;
        case 44003:
            return &ptr->unk35C;
        case 44004:
            return &ptr->unk364;
        case 44005:
            return &ptr->unk36C;
        case 44006:
            return &ptr->unk374;
        case 44007:
            return &ptr->unk37C;
        case 44008:
            return &ptr->unk384;
        case 44009:
            return &ptr->unk38C;
        case 44010:
            return &ptr->unk468;
        case 44011:
            return &ptr->unk474;
        case 44012:
            return &ptr->unk480;
        case 44013:
            return &ptr->unk48C;
        case 44014:
            return &ptr->unk498;
        case 44015:
            return &ptr->unk39C;
        case 44016:
            return &ptr->unk3B4;
        case 44017:
            return &ptr->unk3CC;
        case 44018:
            return &ptr->unk3E4;
        case 44019:
            return &ptr->unk3FC;
        case 44020:
            return &ptr->unk414;
        case 44021:
            return &ptr->unk42C;
        case 44022:
            return &ptr->unk450;
        case 44023:
            return &ptr->unk4A4;
        case 44024:
            return &ptr->unk520;
        case 44025:
            return &ptr->unk59C;
        case 44026:
            return &ptr->unk618;
        case 44027:
            return &ptr->unk694;
        default:
            return nullptr;
    }
}

emRayquazaParamAccesser::~emRayquazaParamAccesser() { }
