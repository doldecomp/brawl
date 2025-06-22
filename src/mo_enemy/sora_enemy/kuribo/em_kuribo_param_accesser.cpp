#include <em/em_create.h>
#include <em/em_extend_param_accesser.h>
#include <em/kuribo/em_kuribo_param_accesser.h>
#include <em/resource/em_resource_module_impl.h>

emKuriboParamAccesser g_emGoombaParamAccesser;

emKuriboParamAccesser::emKuriboParamAccesser()
    : emExtendParamAccesser(Enemy_Goomba) { }

float emKuriboParamAccesser::getParamFloat(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 4000:
            return ptr->unk380;
        default:
            return 0.0f;
    }
}

s32 emKuriboParamAccesser::getParamInt(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 24000:
            return ptr->unk37C.i;
        default:
            return 0;
    }
}

void* emKuriboParamAccesser::getParamIndefinite(soModuleAccesser* acc, s32 p2) {
    UnkParamAccesser* ptr = dynamic_cast<emResourceModuleImpl&>(
        acc->getResourceModule()).unk2C;
    switch (p2) {
        case 44000:
            return ptr;
        case 44001:
            return &ptr->unk2C0;
        case 44002:
            return &ptr->unk32C;
        case 44003:
            return &ptr->unk36C;
        case 44004:
            return &ptr->unk374;
        case 44005:
            return &ptr->unk384;
        default:
            return nullptr;
    }
}

emKuriboParamAccesser::~emKuriboParamAccesser() { }
