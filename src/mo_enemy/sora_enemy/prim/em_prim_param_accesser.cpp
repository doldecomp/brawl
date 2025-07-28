#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/prim/em_prim_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emPrimParamAccesser g_emPrimidParamAccesser;

emPrimParamAccesser::emPrimParamAccesser()
    : emExtendParamAccesser(Enemy_Primid) {

    emExtendParamAccesser::reset(this, 28);
    emExtendParamAccesser::reset(this, 31);
    emExtendParamAccesser::reset(this, 32);
    emExtendParamAccesser::reset(this, 33);
    emExtendParamAccesser::reset(this, 34);
    emExtendParamAccesser::reset(this, 35);
}

float emPrimParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk1330;
        case 4001:
            return ptr->unk1334;
        case 4002:
            return ptr->unk1338;
        case 4003:
            return ptr->unk133C;
        case 4004:
            return ptr->unk1340;
        case 4005:
            return ptr->unk1358;
        case 4006:
            return ptr->unk135C;
        case 4007:
            return ptr->unk1360;
        case 4008:
            return ptr->unk13AC;
        default:
            return 0.0f;
    }
}

s32 emPrimParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk1344;
        default:
            return 0;
    }
}

void* emPrimParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unkD80;
        case 44002:
            return &ptr->unkF0C;
        case 44003:
            return &ptr->unk108C;
        case 44004:
            return &ptr->unk10B0;
        case 44005:
            return &ptr->unk10C0;
        case 44006:
            return &ptr->unk10FC;
        case 44007:
            return &ptr->unk1144;
        case 44008:
            return &ptr->unk1180;
        case 44009:
            return &ptr->unk11BC;
        case 44010:
            return &ptr->unk1204;
        case 44011:
            return &ptr->unk1240;
        case 44012:
            return &ptr->unk1258;
        case 44013:
            return &ptr->unk1270;
        case 44014:
            return &ptr->unk1288;
        case 44015:
            return &ptr->unk12A0;
        case 44016:
            return &ptr->unk12B8;
        case 44017:
            return &ptr->unk12D0;
        case 44018:
            return &ptr->unk12E8;
        case 44019:
            return &ptr->unk1300;
        case 44020:
            return &ptr->unk1318;
        case 44021:
            return &ptr->unk1348;
        case 44022:
            return &ptr->unk1350;
        case 44023:
            return &ptr->unk1364;
        case 44024:
            return &ptr->unk1374;
        case 44025:
            return &ptr->unk137C;
        case 44026:
            return &ptr->unk138C;
        case 44027:
            return &ptr->unk139C;
        case 44028:
            return &ptr->unk13B0;
        case 44029:
            return &ptr->unk142C;
        case 44030:
            return &ptr->unk14A8;
        case 44031:
            return &ptr->unk1524;
        case 44032:
            return &ptr->unk15C8;
        case 44033:
            return &ptr->unk15A0;
        default:
            return nullptr;
    }
}

emPrimParamAccesser::~emPrimParamAccesser() { }
