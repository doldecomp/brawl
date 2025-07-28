#include <so/so_module_accesser.h>
#include <em/em_ai_module_impl.h>
#include <em/em_area_module_impl.h>
#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/porky/em_porky_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>
#include <em/enemy.h>

emPorkyParamAccesser g_emPorkyParamAccesser;

emPorkyParamAccesser::emPorkyParamAccesser()
    : emExtendParamAccesser(Enemy_Boss_Porky) { }

float emPorkyParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk61C;
        case 4001:
            return ptr->unk620;
        case 4002:
            return ptr->unk624;
        case 4003:
            return ptr->unk628;
        case 4004:
            return ptr->unk62C;
        default:
            return 0.0f;
    }
}

s32 emPorkyParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk60C;
        case 24001:
            return ptr->unk610;
        case 24002:
            return ptr->unk614;
        case 24003:
            return ptr->unk618;
        default:
            return 0;
    }
}

void* emPorkyParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    s32 r29;
    bool r28;
    bool r31;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk540;
        case 44002:
            return &ptr->unk5AC;
        case 44003:
            return &ptr->unk630;
        case 44004:
            return &ptr->unk638;
        case 44005:
            return &ptr->unk640;
        case 44006:
            return &ptr->unk648;
        case 44007:
            return &ptr->unk650;
        case 44008:
            return &ptr->unk660;
        case 44009:
            return &ptr->unk670;
        case 44010:
            return &ptr->unk680;
        case 44011:
            return &ptr->unk690;
        case 44012:
            return &ptr->unk6A0;
        case 44013:
            return &ptr->unk6B0;
        case 44014:
            return &ptr->unk6C0;
        case 44015:
            return &ptr->unk6CC;
        case 44016:
            return &ptr->unk6D8;
        case 44017:
            return &ptr->unk6E4;
        case 44018:
            return &ptr->unk6F0;
        case 44019:
            return &ptr->unk6FC;
        case 44020:
            return &ptr->unk708;
        case 44021:
            return &ptr->unk72C;
        case 44022:
            return &ptr->unk750;
        case 44023:
            return &ptr->unk774;
        case 44024:
            r29 = dynamic_cast<Enemy&>(acc->getStageObject())
                                      .getAIModule().getCurrentAIInfo()->unk4;
            r31 = emAreaModuleImpl::isTargetFoundDir(acc, r29, 2);
            r28 = false;
            if (0 == emAreaModuleImpl::getTargetFoundDistance(acc, r29)) {
                r28 = true;
            }
            if (r31 == true) {
                if (r28 == true) {
                    return &ptr->unk708;
                } else {
                    return &ptr->unk750;
                }
            } else {
                if (r28 == true) {
                    return &ptr->unk72C;
                } else {
                    return &ptr->unk774;
                }
            }
        case 44025:
            return &ptr->unk798;
        case 44026:
            return &ptr->unk7B0;
        case 44027:
            return &ptr->unk7D4;
        case 44028:
            r29 = dynamic_cast<Enemy&>(acc->getStageObject())
                                      .getAIModule().getCurrentAIInfo()->unk4;
            r28 = false;
            if (0 == emAreaModuleImpl::getTargetFoundDistance(acc, r29)) {
                r28 = true;
            }
            if (r28 == true) {
                return &ptr->unk7B0;
            } else {
                return &ptr->unk7D4;
            }
        case 44029:
            return &ptr->unk7F8;
        case 44030:
            return &ptr->unk810;
        case 44031:
            return &ptr->unk828;
        case 44032:
            return &ptr->unk8A4;
        case 44033:
            return &ptr->unk920;
        case 44034:
            return &ptr->unk99C;
        default:
            return nullptr;
    }
}

emPorkyParamAccesser::~emPorkyParamAccesser() { }
