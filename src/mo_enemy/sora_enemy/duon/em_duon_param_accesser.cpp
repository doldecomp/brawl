#include <so/so_module_accesser.h>
#include <em/em_ai_module_impl.h>
#include <em/em_area_module_impl.h>
#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/duon/em_duon_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>
#include <em/enemy.h>

emDuonParamAccesser g_emDuonParamAccesser;

emDuonParamAccesser::emDuonParamAccesser()
    : emExtendParamAccesser(Enemy_Boss_Duon) { }

float emDuonParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk3BC;
        case 4001:
            return ptr->unk3C0;
        case 4002:
            return ptr->unk3C4;
        default:
            return 0.0f;
    }
}

s32 emDuonParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk3B0;
        case 24001:
            return ptr->unk3B4;
        case 24002:
            return ptr->unk3B8;
        default:
            return 0;
    }
}

void* emDuonParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    emAIInfo* aiInfo;
    bool r31;
    s32 r4;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk2C0;
        case 44002:
            return &ptr->unk350;
        case 44003:
            return &ptr->unk3C8;
        case 44004:
            return &ptr->unk3D0;
        case 44005:
            return &ptr->unk3D8;
        case 44006:
            return &ptr->unk3E8;
        case 44007:
            return &ptr->unk3F8;
        case 44008:
            return &ptr->unk404;
        case 44009:
            return &ptr->unk410;
        case 44010:
            r4 = dynamic_cast<Enemy&>(acc->getStageObject())
                                      .getAIModule().getCurrentAIInfo()->unk4;
            r31 = false;
            if (0 == emAreaModuleImpl::getTargetFoundDistance(acc, r4)) {
                r31 = true;
            }
            if (r31 == true) {
                return &ptr->unk428;
            }
            return &ptr->unk44C;
        case 44011:
            return &ptr->unk470;
        case 44012:
            r4 = dynamic_cast<Enemy&>(acc->getStageObject())
                                      .getAIModule().getCurrentAIInfo()->unk4;
            r31 = false;
            if (0 == emAreaModuleImpl::getTargetFoundDistance(acc, r4)) {
                r31 = true;
            }
            if (r31 == true) {
                return &ptr->unk488;
            }
            return &ptr->unk4AC;
        case 44013:
            r4 = dynamic_cast<Enemy&>(acc->getStageObject())
                                      .getAIModule().getCurrentAIInfo()->unk4;
            r31 = false;
            if (0 == emAreaModuleImpl::getTargetFoundDistance(acc, r4)) {
                r31 = true;
            }
            if (r31 == true) {
                return &ptr->unk4D0;
            }
            return &ptr->unk4F4;
        case 44014:
            return &ptr->unk518;
        case 44015:
            return &ptr->unk594;
        case 44016:
            return &ptr->unk610;
        case 44017:
            return &ptr->unk68C;
        case 44018:
            return &ptr->unk708;
        case 44019:
            return &ptr->unk784;
        default:
            return nullptr;
    }
}

emDuonParamAccesser::~emDuonParamAccesser() { }
