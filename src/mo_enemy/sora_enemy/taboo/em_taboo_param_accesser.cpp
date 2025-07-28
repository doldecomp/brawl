#include <so/so_module_accesser.h>
#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/taboo/em_taboo_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>
#include <em/enemy.h>

emTabooParamAccesser g_emTabuuParamAccesser;

emTabooParamAccesser::emTabooParamAccesser()
    : emExtendParamAccesser(Enemy_Boss_Tabuu) { }

float emTabooParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk31C;
        case 4001:
            return ptr->unk320;
        case 4002:
            return ptr->unk324;
        case 4003:
            return ptr->unk328;
        case 4004:
            return ptr->unk32C.f;
        case 4005:
            return ptr->unk30C;
        case 4006:
            return ptr->unk310;
        case 4007:
            return ptr->unk314;
        case 4008:
            return ptr->unk318;
        default:
            return 0.0f;
    }
}

s32 emTabooParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk304;
        case 24001:
            return ptr->unk308;
        default:
            return 0;
    }
}

void* emTabooParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk2C0;
        case 44002:
            return &ptr->unk2E4;
        case 44003:
            return &ptr->unk330;
        case 44004:
            return &ptr->unk338;
        case 44005:
            return &ptr->unk340;
        case 44006:
            return &ptr->unk348;
        case 44007:
            return &ptr->unk358;
        case 44008:
            return &ptr->unk368;
        case 44009:
            return &ptr->unk378;
        case 44010:
            return &ptr->unk388;
        case 44011:
            return &ptr->unk398;
        case 44012:
            return &ptr->unk678;
        case 44013:
            return &ptr->unk684;
        case 44014:
            return &ptr->unk690;
        case 44015:
            return &ptr->unk69C;
        case 44016:
            return &ptr->unk6A8;
        case 44017:
            return &ptr->unk6B4;
        case 44018:
            return &ptr->unk6C0;
        case 44019:
            return &ptr->unk6CC;
        case 44020:
            return &ptr->unk6D8;
        case 44021:
            return &ptr->unk6E4;
        case 44022:
            return &ptr->unk6F0;
        case 44023:
            return &ptr->unk6FC;
        case 44024:
            return &ptr->unk708;
        case 44025:
            return &ptr->unk714;
        case 44026:
            return &ptr->unk720;
        case 44027:
            return &ptr->unk72C;
        case 44028:
            return &ptr->unk738;
        case 44029:
            return &ptr->unk744;
        case 44030:
            return &ptr->unk750;
        case 44031:
            return &ptr->unk75C;
        case 44032:
            return &ptr->unk768;
        case 44033:
            return &ptr->unk774;
        case 44034:
            return &ptr->unk780;
        case 44035:
            return &ptr->unk78C;
        case 44036:
            return &ptr->unk798;
        case 44037:
            return &ptr->unk7A4;
        case 44038:
            return &ptr->unk7B0;
        case 44039:
            return &ptr->unk7BC;
        case 44040:
            return &ptr->unk7C8;
        case 44041:
            return &ptr->unk3A8;
        case 44042:
            return &ptr->unk3CC;
        case 44043:
            return &ptr->unk3F0;
        case 44044:
            return &ptr->unk414;
        case 44045:
            return &ptr->unk42C;
        case 44046:
            return &ptr->unk444;
        case 44047:
            return &ptr->unk45C;
        case 44048:
            return &ptr->unk480;
        case 44049:
            return &ptr->unk4A4;
        case 44050:
            return &ptr->unk4C8;
        case 44051:
            return &ptr->unk4EC;
        case 44052:
            return &ptr->unk510;
        case 44053:
            return &ptr->unk534;
        case 44054:
            return &ptr->unk594;
        case 44055:
            return &ptr->unk5AC;
        case 44056:
            return &ptr->unk5C4;
        case 44057:
            return &ptr->unk5DC;
        case 44058:
            return &ptr->unk5F4;
        case 44059:
            return &ptr->unk60C;
        case 44060:
            return &ptr->unk630;
        case 44061:
            return &ptr->unk648;
        case 44062:
            return &ptr->unk660;
        case 44063:
            return &ptr->unk7D4;
        case 44064:
            return &ptr->unk850;
        case 44065:
            return &ptr->unk8CC;
        case 44066:
            return &ptr->unk948;
        case 44067:
            return &ptr->unk9C4;
        case 44068:
            return &ptr->unk9D8;
        default:
            return nullptr;
    }
}

emTabooParamAccesser::~emTabooParamAccesser() { }
