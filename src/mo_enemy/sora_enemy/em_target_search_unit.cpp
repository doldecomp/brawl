#include <em/em_area_module_impl.h>
#include <em/em_target_search_unit.h>
#include <so/so_value_accesser.h>

emTargetSearchUnit::emTargetSearchUnit() : soTargetSearchUnit() { }

emTargetSearchUnit::~emTargetSearchUnit() { }

void emTargetSearchUnit::initInterval(soModuleAccesser* acc) {
    soTargetSearchUnit::initInterval(acc);
    if (unk14 > 0) {
        float f1 = soValueAccesser::getValueFloat(acc, 0x1100000C, 0);
        float f3 = unk4->unk14;
        if (0.0f != f3) {
            float f0, f2;
            f2 = unk14;
            f0 = f3 * f1;
            unk14 = f2 + f0;
        }
    }
}

bool emTargetSearchUnit::checkTargetExist(soModuleAccesser* acc, u32 p2) {
    return emAreaModuleImpl::isExistTarget(acc, p2);
}

bool emTargetSearchUnit::checkTargetInArea(soModuleAccesser* acc, u32 p2, u32 p3) {
    if (p2 == -1) {
        return false;
    }
    emAreaModuleImpl& areaMod = dynamic_cast<emAreaModuleImpl&>(acc->getAreaModule());
    return areaMod.checkArea(acc, p2, p3);
}

Vec3f emTargetSearchUnit::getTargetPos(soModuleAccesser* acc, u32 p2) {
    return emAreaModuleImpl::getTargetPos(acc, p2, true);
}

Vec3f emTargetSearchUnit::getSelfPos(soModuleAccesser* acc) {
    return emAreaModuleImpl::getTargetPos(acc, 4, true);
}
