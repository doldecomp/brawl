#include "wn/wn_em_simple.h"
#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/em_weapon_manager.h>
#include <em/bosspackun/em_bosspackun_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emBosspackunParamAccesser g_emPeteyPiranhaParamAccesser;

emBosspackunParamAccesser::emBosspackunParamAccesser()
    : emExtendParamAccesser(Enemy_Boss_PeteyPiranha) { }

float emBosspackunParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    u32 taskId;
    wnemSimple* wn;
    float f1;
    switch (p2) {
        case 4000:
            return ptr->unk150;
        case 4001:
        case 4002:
            taskId = acc->m_stageObject->m_taskId;
            if (taskId == -1) {
                return 100.0f;
            }
            if (p2 == 4001) {
                wn = emWeaponManager::getInstance()->GetManagedWeapon(taskId, 0, 0);
            } else {
                wn = emWeaponManager::getInstance()->GetManagedWeapon(taskId, 1, 0);
            }

            if (!wn) {
                return 100.0f;
            }

            f1 = wn->unk21D8;
            if (f1 <= 0.0f) {
                f1 = 1.0f;
            }
            return 100.0f * (wn->unk21D4 / f1);
        default:
            return 0.0f;
    }
}

s32 emBosspackunParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk144;
        case 24001:
            return ptr->unk148;
        case 24002:
            return ptr->unk14C;
        default:
            return 0;
    }
}

void* emBosspackunParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk100;
        case 44002:
            return &ptr->unk124;
        case 44003:
            return &ptr->unk154;
        case 44004:
            return &ptr->unk164;
        case 44005:
            return &ptr->unk174;
        case 44006:
            return &ptr->unk17C;
        case 44007:
            return &ptr->unk188;
        case 44008:
            return &ptr->unk194;
        case 44009:
            return &ptr->unk1AC;
        case 44010:
            return &ptr->unk1D0;
        case 44011:
            return &ptr->unk1E8;
        case 44012:
            return &ptr->unk200;
        case 44013:
            return &ptr->unk27C;
        case 44014:
            return &ptr->unk2F8;
        case 44015:
            return &ptr->unk314;
        default:
            return nullptr;
    }
}

emBosspackunParamAccesser::~emBosspackunParamAccesser() { }
