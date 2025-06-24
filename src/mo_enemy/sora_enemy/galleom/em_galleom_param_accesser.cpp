#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/galleom/em_galleom_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emGalleomParamAccesser g_emGalleomParamAccesser;

emGalleomParamAccesser::emGalleomParamAccesser()
    : emExtendParamAccesser(Enemy_Boss_Galleom) { }

float emGalleomParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk40C;
        case 4001:
            return ptr->unk410;
        case 4002:
            return ptr->unk414;
        case 4003:
            return ptr->unk418;
        default:
            return 0.0f;
    }
}

s32 emGalleomParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk404;
        case 24001:
            return ptr->unk408;
        default:
            return 0;
    }
}

void* emGalleomParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk3C0;
        case 44002:
            return &ptr->unk3E4;
        case 44003:
            return &ptr->unk41C;
        case 44004:
            return &ptr->unk424;
        case 44005:
            return &ptr->unk42C;
        case 44006:
            return &ptr->unk434;
        case 44007:
            return &ptr->unk43C;
        case 44008:
            return &ptr->unk56C;
        case 44009:
            return &ptr->unk578;
        case 44010:
            return &ptr->unk584;
        case 44011:
            return &ptr->unk590;
        case 44012:
            return &ptr->unk59C;
        case 44013:
            return &ptr->unk5A8;
        case 44014:
            return &ptr->unk44C;
        case 44015:
            return &ptr->unk464;
        case 44016:
            return &ptr->unk488;
        case 44017:
            return &ptr->unk4AC;
        case 44018:
            return &ptr->unk4D0;
        case 44019:
            return &ptr->unk4F4;
        case 44020:
            return &ptr->unk524;
        case 44021:
            return &ptr->unk548;
        case 44022:
            return &ptr->unk5B4;
        case 44023:
            return &ptr->unk630;
        case 44024:
            return &ptr->unk6AC;
        case 44025:
            return &ptr->unk728;
        default:
            return nullptr;
    }
}

emGalleomParamAccesser::~emGalleomParamAccesser() { }
