#include <em/em_archive.h>
#include <em/em_info.h>
#include <so/so_archive_db.h>
#include <types.h>

emArchive::emArchive(gfArchive* param, gfArchive* brres, gfArchive* enmCommon, gfArchive* primFaceBrres, EnemyKind enemyKind) :
    enmCommonResourceId(0xFFFF),
    brresResourceId(0xFFFF),
    paramResourceId(0xFFFF),
    weaponResourceId(0xFFFF),
    faceTexBrresResourceId(0xFFFF),
    extendBrresResourceId(0xFFFF) {
    paramResourceId = soArchiveDb::getManager(1)->addArchive(param);
    brresResourceId = soArchiveDb::getManager(1)->addArchive(brres);
    enmCommonResourceId = soArchiveDb::getManager(1)->addArchive(enmCommon);
    weaponResourceId = faceTexBrresResourceId = brresResourceId;
    if (emInfo::getInstance()->isPrimKind(enemyKind) == true) {
        extendBrresResourceId = soArchiveDb::getManager(1)->addArchive(primFaceBrres);
    }
}

emArchive::~emArchive() {
    remove();
}

bool emArchive::isComp() const {
    if (paramResourceId != 0xFFFF) {
        utArchiveManager* manager = soArchiveDb::getManager(1);
        if (!manager->isLoaded(paramResourceId, nullptr)) {
            return false;
        }
    }
    if (brresResourceId != 0xFFFF) {
        utArchiveManager* manager = soArchiveDb::getManager(1);
        if (!manager->isLoaded(brresResourceId, nullptr)) {
            return false;
        }
    }
    if (enmCommonResourceId != 0xFFFF) {
        utArchiveManager* manager = soArchiveDb::getManager(1);
        if (!manager->isLoaded(enmCommonResourceId, nullptr)) {
            return false;
        }
    }
    if (extendBrresResourceId != 0xFFFF) {
        utArchiveManager* manager = soArchiveDb::getManager(1);
        if (!manager->isLoaded(extendBrresResourceId, nullptr)) {
            return false;
        }
    }
    return true;
}

void emArchive::remove() {
    if (paramResourceId != 0xFFFF) {
        utArchiveManager* manager = soArchiveDb::getManager(1);
        manager->removeArchive(paramResourceId);
    }
    if (brresResourceId != 0xFFFF) {
        utArchiveManager* manager = soArchiveDb::getManager(1);
        manager->removeArchive(brresResourceId);
    }
    if (enmCommonResourceId != 0xFFFF) {
        utArchiveManager* manager = soArchiveDb::getManager(1);
        manager->removeArchive(enmCommonResourceId);
    }
    if (extendBrresResourceId != 0xFFFF) {
        utArchiveManager* manager = soArchiveDb::getManager(1);
        manager->removeArchive(extendBrresResourceId);
    }
}

u32 emArchive::getWeaponResourceId() const {
    return weaponResourceId;
}
