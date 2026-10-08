// ftManager: the fighter manager. It owns the fighter entries (ftEntryManager) and resource slots (ftSlotManager) and
// is the single entry point the rest of the game uses to start, query and affect fighters.
#include <ft/ft_manager.h>
#include <ft/ft_common_data_accesser.h>
#include <ft/ft_external_value_accesser.h>
#include <gf/gf_task.h>
#include <gf/gf_task_scheduler.h>
#include <it/it_manager.h>
#include <gf/gf_camera.h>
#include <gm/gm_global.h>
#include <mu/menu.h>
#include <snd/snd_system.h>
#include <so/collision/so_collision_manager.h>
#include <ft/ft_audience_manager.h>
#include <so/so_archive_db.h>
#include <so/so_external_value_accesser.h>
#include <sr/sr_common.h>

// HYPOTHESIS: the structure behind ftManager::m_dataProvider; only the flag read by isUseCompressedMode is known.
// Evaluated at each use: the entry manager pointer is reloaded after every call in a loop.
static inline soArray<ftEntry*>& getEntries(const ftManager* manager) {
    return manager->m_entryManager->m_entryArrayVector;
}

static inline ftDataProvider* getSystemData(const ftManager* manager) {
    return manager->m_dataProvider;
}

bool ftManager::isEnableDiscretionFinal() const {
    bool result = false;
    if (m_gameRule != 2) {
        if (m_isDiscretionFinal == true) {
            result = true;
        }
    }
    return result;
}

void ftManager::start() {
    getSystemData(this)->m_isUseCompressedMode = false;
}

void ftManager::quitGame() {
    getSystemData(this)->m_isUseCompressedMode = true;
    m_isGameStarted = false;
    m_isGameSet = false;
    unk6e_04 = false;
}

int ftManager::addSlot() {
    return g_ftSlotManager->addSlot();
}

bool ftManager::isUseCompressedMode() const {
    return getSystemData(this)->m_isUseCompressedMode;
}

bool ftManager::isReadySlot(int slotIndex) const {
    bool result = false;
    ftSlot* slot = &g_ftSlotManager->m_slots[slotIndex];
    if (slot->m_isUnused == false) {
        if (slot->isReady() == true) {
            result = true;
        }
    }
    return result;
}

bool ftManager::isReadyRemoveSlot(int slotIndex) const {
    bool result = false;
    ftSlot* slot = &g_ftSlotManager->m_slots[slotIndex];
    if (slot->m_isUnused == false) {
        if (slot->isReadyRemove() == true) {
            result = true;
        }
    }
    return result;
}

bool ftManager::removeSlot(int slotIndex) {
    g_ftSlotManager->removeSlot(slotIndex);
    return true;
}

void ftManager::addBootResource(int slotIndex, int resId) {
    g_ftSlotManager->m_slots[slotIndex].loadBootResource2ndary(resId);
}

void ftManager::addEntryResource(int slotIndex, int resId) {
    g_ftSlotManager->m_slots[slotIndex].load(resId, 0x2000, 0);
}

void ftManager::addResultResource(int slotIndex, int resId) {
    g_ftSlotManager->m_slots[slotIndex].load(resId, 0x4000, 0);
}

void ftManager::addItemResource(int slotIndex, int itemId) {
    g_ftSlotManager->m_slots[slotIndex].pushItem(itemId);
}

void ftManager::removeTechniqResourceAll() {
    int slotCount = g_ftSlotManager->m_slotCount;
    for (int i = 0; i < slotCount; i++) {
        g_ftSlotManager->m_slots[i].remove(0xFF, 0x7000, 0);
    }
}

void ftManager::removeResourceAll() {
    int slotCount = g_ftSlotManager->m_slotCount;
    for (int i = 0; i < slotCount; i++) {
        g_ftSlotManager->m_slots[i].removeAll();
    }
}

void ftManager::set2PGamesHeapLayout(int layout) {
    g_ftSlotManager->set2PGamesFlexHeapLayout(layout);
}

bool ftManager::isValidEntryId(int entryId) const {
    return m_entryManager->isValid(entryId);
}

bool ftManager::isExistEntry() const {
    soArray<ftEntry*>& entries = m_entryManager->m_entryArrayVector;
    return entries.size() != 0;
}

int ftManager::getEntryCount() const {
    soArray<ftEntry*>& entries = m_entryManager->m_entryArrayVector;
    return entries.size();
}

int ftManager::getEntryIdFromIndex(int index) const {
    soArray<ftEntry*>& entries = m_entryManager->m_entryArrayVector;
    return entries.at(index)->m_entryId;
}

int ftManager::enumEntryId(int entryId) const {
    return m_entryManager->enumEntryId(entryId);
}

int ftManager::enumIncludeEntryId(int entryId) const {
    return m_entryManager->enumIncludeEntryId(entryId);
}

int ftManager::getEntryId(int playerNo) const {
    return m_entryManager->getEntryIdFromPlayerNo(playerNo);
}

// With heart swap the score goes to the partner entry.
int ftManager::getScoreEntryId(int entryId) const {
    if (m_entryManager->getEntity(entryId)->m_heartSwapEntryId != -1) {
        return m_entryManager->getEntity(entryId)->m_heartSwapEntryId;
    } else {
        return entryId;
    }
}

int ftManager::getEntryIdFromAreaId(int areaId) const {
    return m_entryManager->getEntryIdFromAreaId(areaId);
}

int ftManager::getEntryIdFromTaskId(int taskId, int* outInstanceIndex) const {
    return m_entryManager->getEntryIdFromTaskId(taskId, outInstanceIndex);
}


bool ftManager::isReadyKirbyCopyResource(int entryId, int kirbyKind) const {
    ftEntry* entry = m_entryManager->getEntity(entryId);
    return g_ftSlotManager->m_slots[entry->m_slotIndex].isReadyKirbyCopyResource(kirbyKind, -1);
}

bool ftManager::isReadyFinalResource(int entryId) const {
    ftEntry* entry = m_entryManager->getEntity(entryId);
    return g_ftSlotManager->m_slots[entry->m_slotIndex].isReady();
}

// With heart swap in a stock match, a defeated fighter's stock may be spent by the swap partner instead.
// HYPOTHESIS: the rule is 1 for stock matches, and the flag at ftEntry+0x11 (mask 0x02) marks the entry whose body is swapped.
int ftManager::getRealRebirthEntryId(int entryId) {
    if (m_gameRule == 1) {
        ftEntry* entry = m_entryManager->getEntity(entryId);
        int partnerId = entry->m_heartSwapEntryId;
        if (partnerId != -1) {
            if (m_entryManager->getEntity(partnerId)->isHeartSwapped() == true) {
                if (entry->m_owner->getStockCount() > 0) {
                    return partnerId;
                }
            }
        }
    }
    return entryId;
}

void ftManager::startFighter(int entryId, bool unk) {
    m_entryManager->getEntity(entryId)->toStartSequence(unk);
}

void ftManager::startFighter(int entryId, Vec3f* pos, float lr) {
    ftOwner* owner = m_entryManager->getEntity(entryId)->m_owner;
    owner->setStartPos(pos);
    owner->setStartLr(lr);
    m_entryManager->getEntity(entryId)->toStartSequence(2);
}

void ftManager::setWarpFighter(int entryId, Vec3f* pos, float lr, u32 flags) {
    m_entryManager->getEntity(entryId)->setWarp(pos, lr, flags);
}

void ftManager::disappearTrainer(int entryId) {
    m_entryManager->getEntity(entryId)->disappearTrainer();
}

void ftManager::standbyFighter(int entryId, int unk) {
    m_entryManager->getEntity(entryId)->standby(unk);
}

void ftManager::standbyFighterAdvFollow(int entryId) {
    m_entryManager->getEntity(entryId)->standbyAdvFollow();
}

void ftManager::standbyAllFighter() {
    int count = getEntries(this).size();
    for (int i = 0; i < count; i++) {
        ftEntry* entry = getEntries(this).at(i);
        m_entryManager->getEntity(entry->m_entryId)->standby(1);
    }
}

// Team of an entry; only in team battles with team attack on is the second argument honoured.
int ftManager::getTeam(int entryId, bool unk2, bool unk3) const {
    bool teamFlag = false;
    if (m_isTeams == true) {
        if (m_isTeamAttack == true) {
            if (unk2 == true) {
                teamFlag = true;
            }
        }
    }
    return m_entryManager->getEntity(entryId)->getTeam(teamFlag, unk3);
}

int ftManager::getPointTeam(int entryId) const {
    return m_entryManager->getEntity(entryId)->m_pointTeam;
}

int ftManager::getTeam2nd(int entryId) const {
    return m_entryManager->getEntity(entryId)->getTeam2nd(true);
}

void ftManager::setVisibilityTrainer(int entryId, bool visible) {
    m_entryManager->getEntity(entryId)->setVisibilityTrainer(visible);
}

void ftManager::setFighterOperationStatus(int entryId, int status) {
    m_entryManager->getEntity(entryId)->m_input->setWhole(status);
}

int ftManager::getFighterOperationStatus(int entryId) {
    ftInput* input = m_entryManager->getEntity(entryId)->m_input;
    bool result = false;
    if (input->unk0_80) {
        if (input->unk8 != 0) {
            result = true;
        }
    }
    return result;
}

void ftManager::setFighterOperationStatusAll(int status) {
    int count = getEntries(this).size();
    for (int i = 0; i < count; i++) {
        getEntries(this).at(i)->m_input->setWhole(status);
    }
}

int ftManager::getFighterOperationType(int entryId) {
    return m_entryManager->getEntity(entryId)->m_input->getType();
}

// Switches an entry between human and CPU control (type 1 is CPU, 0 human).
void ftManager::setFighterOperationType(int entryId, s8 type) {
    ftEntry* entry = m_entryManager->getEntity(entryId);
    entry->m_input->setType(type);
    entry->m_owner->setOperationCpu(type == 1);
    for (int i = 0; i < entry->m_entryCount; i++) {
        Fighter* fighter = entry->m_instances[i].m_fighter;
        if (fighter != NULL) {
            fighter->activateControllerLog(type == 0);
        }
    }
}

void ftManager::setFighterOperationCpuType(int entryId, int cpuType) {
    m_entryManager->getEntity(entryId)->m_input->setCpuType(cpuType);
}

// True while any technique-related resource group is loading or an entry is running a technique, or the data provider is busy.
bool ftManager::isProcessTechnique() const {
    int slotCount = g_ftSlotManager->m_slotCount;
    for (int i = 0; i < slotCount; i++) {
        if (g_ftSlotManager->m_slots[i].isLoaded(0x7000) == true) {
            return true;
        }
    }
    int count = getEntries(this).size();
    for (int i = 0; i < count; i++) {
        if (getEntries(this).at(i)->isProcessTechnique() == true) {
            return true;
        }
    }
    return g_ftDataProvider->isReady() == false;
}

bool ftManager::isCpuActive(int entryId) const {
    if (m_entryManager->isValid(entryId) == false) {
        return false;
    }
    return m_entryManager->getEntity(entryId)->unkF == 6;
}

int ftManager::getFighterCount(int entryId) const {
    if (m_entryManager->isValid(entryId) == false) {
        return 0;
    }
    return m_entryManager->getEntity(entryId)->m_entryCount;
}

// instanceIndex -1 selects the active instance (for Pokemon Trainer and Zelda/Sheik style changes).
Fighter* ftManager::getFighter(int entryId, int instanceIndex) const {
    if (m_entryManager->isValid(entryId) == false) {
        return NULL;
    }
    if (instanceIndex != -1) {
        return m_entryManager->getEntity(entryId)->m_instances[instanceIndex].m_fighter;
    }
    ftEntry* entry = m_entryManager->getEntity(entryId);
    return entry->m_instances[(u8)entry->m_activeInstanceIndex].m_fighter;
}

// Only the Ice Climbers have a sub fighter (Nana, the second instance).
Fighter* ftManager::getSubFighter(int entryId) const {
    if (m_entryManager->isValid(entryId) == false) {
        return NULL;
    }
    if (m_entryManager->getEntity(entryId)->m_characterKind == Character_IceClimbers) {
        return m_entryManager->getEntity(entryId)->m_instances[1].m_fighter;
    }
    return NULL;
}



bool ftManager::isFighterActivate(int entryId, int instanceIndex) const {
    Fighter* fighter = getFighter(entryId, instanceIndex);
    bool result = false;
    if (fighter != NULL) {
        if (fighter->isActive()) {
            result = true;
        }
    }
    return result;
}

bool ftManager::isSubFighterActivate(int entryId) const {
    Fighter* fighter = getSubFighter(entryId);
    bool result = false;
    if (fighter != NULL) {
        if (fighter->isActive()) {
            result = true;
        }
    }
    return result;
}

// The sub fighter counts as dead (gone) once it is in the "Unloaded" status (0x10B).
bool ftManager::isSubFighterDead(int entryId) const {
    Fighter* fighter = getSubFighter(entryId);
    bool result = false;
    if (fighter != NULL) {
        if (fighter->isActive()) {
            if (soExternalValueAccesser::getStatusKind(fighter) == 0x10B) {
                result = true;
            }
        }
    }
    return result;
}

// A fighter's position can be read as long as it is active and not outside the stage field.
bool ftManager::isFighterPositionAccessable(int entryId, int instanceIndex) const {
    Fighter* fighter = getFighter(entryId, instanceIndex);
    bool result = false;
    if (fighter != NULL) {
        if (fighter->isActive()) {
            if (soExternalValueAccesser::getSituationKind(fighter) != Situation_Outfield) {
                result = true;
            }
        }
    }
    return result;
}

bool ftManager::isSubFighterPositionAccessable(int entryId) const {
    Fighter* fighter = getSubFighter(entryId);
    bool result = false;
    if (fighter != NULL) {
        if (fighter->isActive()) {
            if (soExternalValueAccesser::getSituationKind(fighter) != Situation_Outfield) {
                result = true;
            }
        }
    }
    return result;
}

bool ftManager::isFighterEnableWarp(int entryId) const {
    Fighter* fighter = getFighter(entryId, -1);
    bool result = false;
    if (fighter != NULL) {
        if (fighter->isEnableWarp()) {
            result = true;
        }
    }
    return result;
}

int ftManager::getCurrentFighterNo(int entryId) const {
    return static_cast<u8>(m_entryManager->getEntity(entryId)->m_activeInstanceIndex);
}

int ftManager::getFighterNo(int entryId, int kind) const {
    return m_entryManager->getEntity(entryId)->isExistFighter(kind);
}

int ftManager::getFighterGmKind(int entryId) const {
    return m_entryManager->getEntity(entryId)->m_characterKind;
}

int ftManager::getResultFighterGmKind(int entryId) const {
    return m_entryManager->getEntity(entryId)->getCurrentInstanceGmKind();
}

const char* ftManager::getFighterName(int entryId) const {
    int gmKind = m_entryManager->getEntity(entryId)->getCurrentInstanceGmKind();
    return muMenu::exchangeMuStockchkind2MuCharName(muMenu::exchangeGmCharacterKind2MuStockchkind(gmKind));
}

Vec3f ftManager::getFighterCursorPos(int entryId, int instanceIndex) const {
    return ftExternalValueAccesser::getCursorPos(getFighter(entryId, instanceIndex));
}

Vec3f ftManager::getFighterCenterPos(int entryId, int instanceIndex) const {
    return ftExternalValueAccesser::getHipPos(getFighter(entryId, instanceIndex));
}

Vec2f* ftManager::getFighterRhombusCenterPos(int entryId, int instanceIndex) const {
    return soExternalValueAccesser::getRhombusCenterPos(getFighter(entryId, instanceIndex));
}

float ftManager::getFighterLr(int entryId, int instanceIndex) const {
    return soExternalValueAccesser::getLr(getFighter(entryId, instanceIndex));
}

ftOwner* ftManager::getOwner(int entryId) const {
    return m_entryManager->getEntity(entryId)->m_owner;
}

// HYPOTHESIS: a sub owner (the second fighter of a pair) is embedded in the owner object at +0xD54.
ftOwner* ftManager::getSubOwner(int entryId) const {
    return reinterpret_cast<ftOwner*>(reinterpret_cast<u8*>(m_entryManager->getEntity(entryId)->m_owner) + 0xD54);
}

void* ftManager::getInput(int entryId) const {
    return *reinterpret_cast<void**>(reinterpret_cast<u8*>(m_entryManager->getEntity(entryId)->m_owner) + 4);
}

void* ftManager::getSubInput(int entryId) const {
    return *reinterpret_cast<void**>(reinterpret_cast<u8*>(m_entryManager->getEntity(entryId)->m_owner) + 0xD58);
}

s32 ftManager::getSlotNo(s32 entryId) const {
    ftEntry* entry = m_entryManager->getEntity(entryId);
    return g_ftSlotManager->m_slots[entry->m_slotIndex].m_slotNo;
}

int ftManager::getPlayerNo(int entryId) const {
    if (m_entryManager->isValid(entryId) == false) {
        return -1;
    }
    return m_entryManager->getEntity(entryId)->m_playerNo;
}

int ftManager::getRank(int entryId) const {
    if (m_entryManager->isValid(entryId) == false) {
        return 0;
    }
    return m_entryManager->getEntity(entryId)->getRank();
}

int ftManager::getRankPoint(int entryId) const {
    if (m_entryManager->isValid(entryId) == false) {
        return 0;
    }
    return m_entryManager->getEntity(entryId)->getRankPoint();
}

int ftManager::getKirbyCopyResourceCount(int entryId) const {
    ftEntry* entry = m_entryManager->getEntity(entryId);
    return g_ftSlotManager->m_slots[entry->m_slotIndex].getKirbyResourceCount();
}

int ftManager::getKirbyCopyResourceKind(int entryId, int index) const {
    ftEntry* entry = m_entryManager->getEntity(entryId);
    return g_ftSlotManager->m_slots[entry->m_slotIndex].getKirbyResourceKind(index);
}

// The Kirby copy resource of a slot finished loading (or unloading): tell the entries that use that slot.
void ftManager::onKirbyResourceLoaded(int slotIndex, int index) {
    int count = getEntries(this).size();
    for (int i = 0; i < count; i++) {
        ftEntry* entry = getEntries(this).at(i);
        if (slotIndex == entry->m_slotIndex) {
            entry->notifyKirbyResourceLoaded(index);
        }
    }
}

void ftManager::onKirbyResourceUnLoaded(int slotIndex, int index) {
    int count = getEntries(this).size();
    for (int i = 0; i < count; i++) {
        ftEntry* entry = getEntries(this).at(i);
        if (slotIndex == entry->m_slotIndex) {
            entry->notifyKirbyResourceUnLoaded(index);
        }
    }
}

// Tells every entry that does not use the slot that one of its fighters left.
void ftManager::exitFighter(int slotIndex, int unk) {
    int count = getEntries(this).size();
    for (int i = 0; i < count; i++) {
        ftEntry* entry = getEntries(this).at(i);
        if (slotIndex != entry->m_slotIndex) {
            entry->notifyExitFighter(slotIndex, unk);
        }
    }
}

void ftManager::setTemporaryCamera(int entryId, float unk1, int unk2, int unk3, int unk4) {
    m_entryManager->getEntity(entryId)->setTemporaryCamera(unk1, unk2, unk3, unk4);
}

void ftManager::setInterporateTemporaryCamera(int entryId, float unk1, float unk2, int unk3, int unk4) {
    m_entryManager->getEntity(entryId)->setIntarpolateTemporaryCamera(unk1, unk2, unk3, unk4);
}

// Coins (coin battle) are credited to the heart swap partner while hearts are swapped.
int ftManager::getCoin(int entryId) const {
    ftEntry* entry = m_entryManager->getEntity(entryId);
    return m_entryManager->getEntity(entry->m_heartSwapEntryId != -1 ? entry->m_heartSwapEntryId : entryId)->m_owner->getCoin();
}

void ftManager::pickupCoin(int entryId, int amount) {
    ftEntry* entry = m_entryManager->getEntity(entryId);
    ftOwner* owner = m_entryManager->getEntity(entry->m_heartSwapEntryId != -1 ? entry->m_heartSwapEntryId : entryId)->m_owner;
    owner->addCoin(amount);
    owner->setPickupCoin(amount + owner->getPickupCoin());
}

void ftManager::lostCoin(int entryId, int amount, bool unk) {
    ftEntry* entry = m_entryManager->getEntity(entryId);
    ftOwner* owner = m_entryManager->getEntity(entry->m_heartSwapEntryId != -1 ? entry->m_heartSwapEntryId : entryId)->m_owner;
    owner->addLostCoin(amount);
    if (unk == true) {
        owner->addCoin(-amount);
    }
}

void ftManager::generateCoin(int entryId, int amount) {
    ftEntry* entry = m_entryManager->getEntity(entryId);
    m_entryManager->getEntity(entry->m_heartSwapEntryId != -1 ? entry->m_heartSwapEntryId : entryId)->m_owner->addGenerateCoin(amount);
}

void ftManager::toChange(int entryId, int unk1, int unk2, int unk3) {
    m_entryManager->getEntity(entryId)->startChange(unk1, unk2, unk3);
}

void ftManager::toChangeAppear(int entryId, float unk1, int unk2, int unk3) {
    m_entryManager->getEntity(entryId)->prepareChange(unk1, unk2, unk3);
}

void ftManager::setContNo(int entryId, int contNo) {
    m_entryManager->getEntity(entryId)->setContNo(contNo);
}

bool ftManager::addDragoon(int entryId, u32 variation) {
    return m_entryManager->getEntity(entryId)->addDragoon(variation, true);
}

void ftManager::removeDragoon(int entryId, int index) {
    m_entryManager->getEntity(entryId)->removeDragoon(index, true);
}

void ftManager::removeDragoonAll(int entryId) {
    m_entryManager->getEntity(entryId)->removeDragoonAll(true);
}

int ftManager::getDragoonCount(int entryId) {
    return m_entryManager->getEntity(entryId)->getDragoonCount(true);
}

int ftManager::getDragoonVariation(int entryId, int index) {
    return m_entryManager->getEntity(entryId)->getDragoonVariation(index, true);
}

void ftManager::setHeartSwap(int entryId1, int entryId2) {
    m_entryManager->startSwap(entryId1, entryId2);
}

// True while hearts are swapped.
bool ftManager::isProcessHeartSwap() const {
    return m_entryManager->m_isProcessHeartSwap;
}

bool ftManager::isProcessHeartSwap(int entryId) const {
    return m_entryManager->getEntity(entryId)->m_heartSwapEntryId != -1;
}

int ftManager::getPokeTrainerInstanceHeap(int entryId) const {
    ftEntry* entry = m_entryManager->getEntity(entryId);
    return g_ftSlotManager->m_slots[entry->m_slotIndex].m_pokeTrainerInstanceHeap;
}

void ftManager::setCurry(int entryId) {
    m_entryManager->getEntity(entryId)->setCurry();
}

void ftManager::setZoom(int entryId, float unk1, int unk2, int unk3) {
    m_entryManager->getEntity(entryId)->setZoom(unk1, unk2, unk3);
}

void ftManager::setScaling(int entryId, Fighter::Scaling::Kind kind, Fighter::Scaling::Type type) {
    m_entryManager->getEntity(entryId)->setScaling(kind, type);
}

void ftManager::setInfiniteScaling(int entryId, Fighter::Scaling::Kind kind, Fighter::Scaling::Type type) {
    m_entryManager->getEntity(entryId)->m_owner->setInfiniteScaling(kind, type);
    m_entryManager->getEntity(entryId)->setScaling(kind, type);
}

void ftManager::setSuperStar(int entryId) {
    m_entryManager->getEntity(entryId)->setSuperStar();
}

void ftManager::setHeal(int entryId, float heal) {
    m_entryManager->getEntity(entryId)->setHeal(heal);
}

void ftManager::notifyEventEntryEnd(int entryId) {
    m_entryManager->getEntity(entryId)->entryEnd();
}

void ftManager::notifyEventResultEnd(int entryId) {
    m_entryManager->getEntity(entryId)->resultEnd();
}

void ftManager::notifyReplacePokeTrainer(int unk) {
    int count = getEntries(this).size();
    for (int i = 0; i < count; i++) {
        getEntries(this).at(i)->notifyReplacePokeTrainer(unk);
    }
}

void ftManager::notifyEventKirbyCopySetup(int entryId, int unk) {
    ftEntry* entry = m_entryManager->getEntity(entryId);
    g_ftSlotManager->m_slots[entry->m_slotIndex].notifyKirbyCopySetup(unk);
}

void ftManager::notifyEventKirbyCopyCancel(int entryId, int unk) {
    ftEntry* entry = m_entryManager->getEntity(entryId);
    g_ftSlotManager->m_slots[entry->m_slotIndex].notifyKirbyCopyCancel(unk);
}

void ftManager::exitFinal(int entryId, int unk) {
    m_entryManager->getEntity(entryId)->exitFinal(unk);
    m_finalEntryId = -1;
    m_finalStatus = -1;
}

void ftManager::setFinalStatus(int status) {
    if (status != m_finalStatus) {
        m_finalStatus = status;
    }
}

void ftManager::cancelFinalStatus() {
    m_finalStatus = -1;
}

void ftManager::notifyDrawDone() {
    m_isWaitingDraw = false;
}

// HYPOTHESIS: selects the parameter pattern (0 or 1) the data lookups use; written by setMode and setParamPattern.
extern int g_ftParamPattern;
// Whether the Pokemon Trainer stamina system is used; setMode sets it for versus (mode 0) and clears it for adventure (mode 1).
extern u8 g_ftPokemonStaminaSystem;

// HYPOTHESIS: set while items are enabled in the match.
extern int g_ftItemEnabled;

// A Final Smash can only be started if Smash Balls are possible: no exclusive special item is active and the Smash Ball is
// switched on, and a discretionary Final Smash is not blocked by the remaining count.
bool ftManager::isAvailableFinal(bool unk) const {
    if (unk7c == false) {
        return false;
    }
    if (g_ftItemEnabled != 0) {
        if (itManager::getInstance()->isExclusiveSpecialItem(-1, true) == true) {
            return false;
        }
        if (itManager::getInstance()->isItemSwitch(0x37) == 0) {
            return false;
        }
    }
    if (unk == true) {
        if (m_noDiscretionFinalCount > 0) {
            return false;
        }
    }
    return true;
}

void ftManager::setFinal(int entryId, bool isDiscretion) {
    if (entryId != m_finalEntryId) {
        if (m_entryManager->getEntity(entryId)->setFinal(isDiscretion) == true) {
            m_finalEntryId = entryId;
            m_finalStatus = -1;
            if (isDiscretion == true) {
                m_noDiscretionFinalCount = ftExternalValueAccesser::getNoDiscretionFinalCount();
            }
        }
    }
}

// Starts the Final Smash of the entry that owns the given task (a fighter or something a fighter created).
void ftManager::setFinalTask(u32 category, u32 taskId) {
    if (category != gfTask::Category_Fighter) {
        gfTask* task = gfTaskScheduler::getInstance()->getTaskById((gfTask::Category)category, taskId);
        if (task != NULL) {
            taskId = soExternalValueAccesser::getTeamOwnerId(&dynamic_cast<StageObject&>(*task));
        }
    }
    int entryId;
    int i;
    int count = getEntries(this).size();
    for (i = 0; i < count; i++) {
        if ((u8)getEntries(this).at(i)->isExistFighter(taskId) != 0xFF) {
            entryId = getEntries(this).at(i)->m_entryId;
            if (entryId != m_finalEntryId) {
                if (m_entryManager->getEntity(entryId)->setFinal(false) == true) {
                    m_finalEntryId = entryId;
                    m_finalStatus = -1;
                }
            }
            return;
        }
    }
}

void ftManager::notifyEventPikminFinalAttack(float unk1, int unk2) {
    int count = getEntries(this).size();
    for (int i = 0; i < count; i++) {
        getEntries(this).at(i)->notifyPikminFinalAttack(unk1, unk2);
    }
}

// An entry lost a stock (or its stamina): updates the dead count and stock, handles heart swap and tells the observers.
void ftManager::setDead(int entryId, int unk1, int unk2) {
    ftEntry* entry = m_entryManager->getEntity(entryId);
    int reportedEntryId = entryId;
    int ownerEntryId = entryId;
    bool skipRespawn = false;
    if (entry->m_heartSwapEntryId != -1) {
        ownerEntryId = entry->m_heartSwapEntryId;
    }
    ftEntry* ownerEntry = m_entryManager->getEntity(ownerEntryId);
    ftOwner* owner = ownerEntry->m_owner;
    owner->setDeadCount(owner->getDeadCount() + 1);
    bool isStamina = m_isStamina;
    if (isStamina == true || m_gameRule == 1) {
        if (isStamina == true) {
            entry->leaveBattle(false);
            if (ownerEntry->isHeartSwapped() == true) {
                reportedEntryId = ownerEntryId;
            }
            skipRespawn = true;
        } else {
            int stock = owner->getStockCount();
            int newStock;
            if (stock < 0) {
                newStock = -1;
            } else {
                newStock = stock - 1;
                if (newStock < 0) {
                    newStock = 0;
                }
            }
            owner->setStockCount(newStock);
            if (newStock == 0) {
                if (m_gameRule == 1) {
                    entry->leaveBattle(false);
                    if (entry->m_heartSwapEntryId != -1) {
                        skipRespawn = true;
                    }
                }
            }
        }
        if (entry->m_heartSwapEntryId != -1) {
            if (ownerEntry->isHeartSwapped() == true) {
                m_entryManager->endSwap(false);
                reportedEntryId = ownerEntryId;
            }
        }
    }
    ftOutsideEventPresenter presenter(m_eventManageModule.getManageId(), entryId);
    presenter.notifyOutsideEventDead(reportedEntryId, owner->getDeadCount(), unk1, skipRespawn == true ? -1 : unk2);
    entry->notifyDead(unk1);
}

// Resets the manager to its default (versus) state.
void ftManager::setDefault() {
    m_mode = 0;
    m_paramPattern = 0;
    unk7c = 0;
    m_isStamina = 0;
    unk6c_80 = false;
    m_isGameStarted = false;
    m_isGameSet = false;
    unk6c_10 = false;
    unk6f_80 = false;
    unk6f_10 = true;
    m_isTeams = false;
    m_isTeamAttack = false;
    m_isDiscretionFinal = false;
    unk6e_10 = false;
    m_noOnePatternOffsett = false;
    m_isHomerun = false;
    unk6e_04 = false;
    unk6b = 0;
    m_gameRule = 0;
    getSystemData(this)->m_isUseCompressedMode = true;
}

void ftManager::setParamPattern(int pattern) {
    switch (pattern) {
    case 0:
        g_ftParamPattern = 0;
        break;
    case 1:
        g_ftParamPattern = 1;
        break;
    }
    m_paramPattern = pattern;
}

void ftManager::setPokemonStaminaSystem(bool enabled) {
    g_ftPokemonStaminaSystem = enabled;
}

// "Ready, GO!": the match starts.
void ftManager::readyGo() {
    m_isGameStarted = true;
    m_isGameSet = false;
    unk6f_40 = false;
    m_noDiscretionFinalCount = ftExternalValueAccesser::getNoDiscretionFinalCount();
}

// "GAME!": the match ended; every owner's transient state is cleared.
void ftManager::gameSet() {
    m_isGameSet = true;
    int count = getEntries(this).size();
    for (int i = 0; i < count; i++) {
        ftEntry* entry = getEntries(this).at(i);
        entry->m_owner->unkA = 0;
        *reinterpret_cast<u8*>(reinterpret_cast<u8*>(entry->m_owner) + 0xD5E) = 0;
    }
}

// Heart swap ends with the opposite fighter's knockout.
void ftManager::toKnockOutHeartSwapOpposite(int entryId, soDamageAttackerInfo* attackerInfo) {
    int partnerId = m_entryManager->getEntity(entryId)->m_heartSwapEntryId;
    m_entryManager->endSwap(false);
    if (m_entryManager->isValid(partnerId) == true) {
        ftEntry* partner = m_entryManager->getEntity(partnerId);
        if (partnerId == attackerInfo->m_indirectEntryId) {
            attackerInfo->m_indirectEntryId = entryId;
        }
        partner->toKnockOut(attackerInfo);
    }
}

// Highest damage among the other entries.
float ftManager::getDamageMax(int excludeEntryId) {
    float damageMax = 0.0f;
    int count = getEntries(this).size();
    for (int i = 0; i < count; i++) {
        if (excludeEntryId != getEntries(this).at(i)->m_entryId) {
            float damage = getEntries(this).at(i)->m_owner->getDamage();
            if (damageMax < damage) {
                damageMax = damage;
            }
        }
    }
    return damageMax;
}

// Thunder (Thunder item): shrinks everyone who is not on the thunder user's team.
void ftManager::setThunder(int inflictingEntryId, int scalingType) {
    ftEntry* entry;
    int i;
    int count = getEntries(this).size();
    for (i = 0; i < count; i++) {
        entry = getEntries(this).at(i);
        if (inflictingEntryId != entry->m_entryId) {
            if (getTeam(inflictingEntryId, true, true) != getTeam(entry->m_entryId, true, true)) {
                entry->setScaling(Fighter::Scaling::Kind_Thunder, scalingType);
            }
        }
    }
}

// Slows every entry that is not on the given team.
void ftManager::setSlow(int inflictingTeam, bool setStatus, int slowStrength, int slowDuration) {
    ftEntry* entry;
    int i;
    int count = getEntries(this).size();
    for (i = 0; i < count; i++) {
        entry = getEntries(this).at(i);
        if (inflictingTeam != getTeam(entry->m_entryId, true, true)) {
            entry->setSlow(setStatus, slowStrength, slowDuration, false);
        }
    }
}

// Timer-based slow (Timer item): slows everyone who is not on the user's team.
void ftManager::setTimerSlow(int inflictingEntryId, bool setStatus, int slowStrength, int slowDuration) {
    m_entryManager->getEntity(inflictingEntryId);
    ftEntry* entry;
    int i;
    int count = getEntries(this).size();
    for (i = 0; i < count; i++) {
        entry = getEntries(this).at(i);
        if (inflictingEntryId != entry->m_entryId) {
            if (getTeam(inflictingEntryId, true, true) != getTeam(entry->m_entryId, true, true)) {
                entry->setSlow(setStatus, slowStrength, slowDuration, true);
            }
        }
    }
}


// A fighter was knocked out. With the same entry id twice it is a self-destruct (suicide count); otherwise the
// winner gets a beat count against the loser's player number. Hearts swapped entries are credited to their partners.
void ftManager::setBeat(int losingEntryId, int winningEntryId) {
    if (losingEntryId == winningEntryId) {
        int ownerEntryId = losingEntryId;
        int partnerId = m_entryManager->getEntity(losingEntryId)->m_heartSwapEntryId;
        if (partnerId != -1) {
            ownerEntryId = partnerId;
        }
        bool redirected;
        // While a Final Smash is running the self-destruct counts as a beat by the Final Smash owner.
        if (m_finalStatus == 1 && losingEntryId != m_finalEntryId) {
            setBeat(losingEntryId, m_finalEntryId);
            redirected = true;
        } else {
            redirected = false;
        }
        if (redirected == false) {
            ftOwner* owner = m_entryManager->getEntity(ownerEntryId)->m_owner;
            owner->setSuicideCount(owner->getSuicideCount() + 1);
            ftOutsideEventPresenter presenter(m_eventManageModule.getManageId(), losingEntryId);
            presenter.notifyOutsideEventSuicide(ownerEntryId);
        }
    } else {
        ftEntry* winningEntry = m_entryManager->getEntity(winningEntryId);
        if (winningEntry->unkF != 7) {
            ftEntry* losingEntry = m_entryManager->getEntity(losingEntryId);
            if (winningEntry->m_heartSwapEntryId != -1) {
                winningEntryId = winningEntry->m_heartSwapEntryId;
            }
            int loserId = losingEntryId;
            if (losingEntry->m_heartSwapEntryId != -1) {
                loserId = losingEntry->m_heartSwapEntryId;
            }
            int loserPlayerNo = m_entryManager->getEntity(loserId)->m_playerNo;
            ftOwner* owner = m_entryManager->getEntity(winningEntryId)->m_owner;
            owner->setBeatCount(loserPlayerNo, owner->getBeatCount(loserPlayerNo) + 1);
            winningEntry->notifyBeat();
            ftOutsideEventPresenter presenter(m_eventManageModule.getManageId(), losingEntryId);
            presenter.notifyOutsideEventBeat(winningEntryId, loserId);
            if (m_noDiscretionFinalCount > 0) {
                m_noDiscretionFinalCount--;
            }
        }
    }
}

// A fighter destroyed itself. Hearts swapped entries are credited to their partner; while a Final Smash is running
// the self-destruct counts as a beat by the Final Smash owner instead.
void ftManager::setSuicide(int entryId) {
    int partnerId = m_entryManager->getEntity(entryId)->m_heartSwapEntryId;
    int ownerEntryId = partnerId != -1 ? partnerId : entryId;
    bool redirected;
    if (m_finalStatus == 1 && entryId != m_finalEntryId) {
        setBeat(entryId, m_finalEntryId);
        redirected = true;
    } else {
        redirected = false;
    }
    if (redirected == false) {
        ftOwner* owner = m_entryManager->getEntity(ownerEntryId)->m_owner;
        owner->setSuicideCount(owner->getSuicideCount() + 1);
        ftOutsideEventPresenter presenter(m_eventManageModule.getManageId(), entryId);
        presenter.notifyOutsideEventSuicide(ownerEntryId);
    }
}

void soDisposeInstanceEventObserver::addObserver(short param1, s8 param2) {
    addObserverSub(param1, this, param2);
}

void ftOutsideEventObserver::addObserver(short param1, s8 param2) {
    addObserverSub(param1, this, param2);
}

// MATCH-ONLY: the manage id of the dispose instance manager's event module (an soEventManageModuleImpl at +0x60)
static inline s16 getDisposeInstanceManageId() {
    return reinterpret_cast<soEventManageModuleImpl*>(reinterpret_cast<u8*>(g_soDisposeInstanceManager) + 0x60)->getManageId();
}

ftManager::ftManager(u32 commonResourceA, u32 commonResourceB) :
    m_mode(0), m_paramPattern(0), m_gameRule(0), unk6b(0),
    unk6c_80(false), m_isGameStarted(false), m_isGameSet(false), unk6c_10(false),
    m_isStamina(0),
    m_isTeams(false), m_isTeamAttack(false), m_isDiscretionFinal(false), unk6e_10(true), m_noOnePatternOffsett(true),
    unk6e_04(false), m_noDeadUp(false), m_isHomerun(false),
    unk6f_80(false), unk6f_40(false), m_isWaitingDraw(false), unk6f_10(true),
    m_finalStatus(-1), m_finalEntryId(-1), m_noDiscretionFinalCount(0), unk7c(false),
    unk80(0), unk84(0), unk88(0),
    m_eventManageEntity(), m_eventManageModule(&m_eventManageEntity),
    m_eventUnit(m_eventManageModule.getManageId(), 0) {
    soDisposeInstanceEventObserver::addObserver(getDisposeInstanceManageId(), -1);
    ftOutsideEventObserver::addObserver(m_eventManageModule.getManageId(), -1);
    soArchiveDb::create(0, 0x60);
    m_dataProvider = new (Heaps::System) ftDataProvider;
    m_slotManager = new (Heaps::System) ftSlotManager(9);
    m_entryManager = new (Heaps::System) ftEntryManager(9);
    m_dataProvider->reqCommon(commonResourceA, commonResourceB, 2);
}

ftManager::~ftManager() {
    delete m_entryManager;
    m_entryManager = nullptr;
    delete m_slotManager;
    m_slotManager = nullptr;
    delete m_dataProvider;
    m_dataProvider = nullptr;
}

// MATCH-ONLY: unnamed sndSystem query (8-byte function at 0x80073D10)
extern "C" bool fn_80073D10(sndSystem* system);
extern float lbl_27_data_4B84;

// The first argument is ignored: the log observer always registers with the static log event manager.
void soLogEventObserver::addObserver(short, s8 param2) {
    addObserverSub(g_soLogEventManager.m_module.getManageId(), this, param2);
}

// Switches the manager between versus (0) and adventure (1) rules.
void ftManager::setMode(int mode) {
    switch (mode) {
    case 0:
        g_ftParamPattern = 0;
        m_paramPattern = 0;
        unk7c = true;
        unk6c_80 = true;
        m_isGameStarted = false;
        m_isDiscretionFinal = true;
        unk6e_10 = true;
        m_noOnePatternOffsett = true;
        m_noDeadUp = false;
        unk6f_80 = false;
        g_ftPokemonStaminaSystem = true;
        break;
    case 1:
        g_ftParamPattern = 1;
        m_paramPattern = 1;
        unk7c = false;
        unk6c_80 = true;
        m_isGameStarted = true;
        m_isDiscretionFinal = false;
        unk6e_10 = false;
        m_noOnePatternOffsett = false;
        m_noDeadUp = true;
        unk6f_80 = true;
        g_ftPokemonStaminaSystem = false;
        break;
    }
    m_mode = mode;
    m_isGameSet = false;
    unk6c_10 = false;
    unk6f_10 = true;
    m_isHomerun = false;
    unk6e_04 = false;
    unk6b = 0;
    g_ftAudienceManager->activate();
    if (g_soCollisionManager == NULL) {
        g_soCollisionManager = new (Heaps::System) soCollisionManager;
    }
    lbl_27_data_4B84 = 3.4028235e38f;
}

void ftManager::stopGame() {
    g_ftAudienceManager->deactivate();
    m_entryManager->endSwap(false);
}

bool ftManager::isResourceRemoveSync() const {
    bool result = false;
    if (m_isWaitingDraw == false) {
        if (g_ftDataProvider->isReady() == true) {
            if (fn_80073D10(g_sndSystem) == true) {
                result = true;
            }
        }
    }
    return result;
}

float ftManager::getFighterCursorForceDispDistance() const {
    return *reinterpret_cast<float*>(reinterpret_cast<u8*>(g_ftCommonDataAccesser.getParamCommon()) + 0x210);
}

// HYPOTHESIS: the entry embeds its event manage module at 0x1D4
s16 ftManager::getEntryEventManageId(int entryId) const {
    return reinterpret_cast<soEventManageModuleImpl*>(reinterpret_cast<u8*>(m_entryManager->getEntity(entryId)) + 0x1D4)->getManageId();
}

void ftManager::notifyDisposeInstance(bool isDispose, int, int taskId) {
    if (isDispose == false) {
        int entryId = m_entryManager->getEntryIdFromTaskId(taskId, NULL);
        if (entryId != -1) {
            m_entryManager->getEntity(entryId)->m_flags11 |= 0x80;
        }
    }
}

void ftManager::processHit() {
    if (g_GameGlobal->isPrevJustGameFrame() == true) {
        m_dataProvider->process();
        m_entryManager->processHit();
    }
}

void ftManager::setControllerRumble(int entryId, int unk1, int unk2, u32 isOn, int unk3) {
    u8 flag = 0;
    if (isOn == 1) {
        flag |= 1;
    }
    m_entryManager->getEntity(entryId)->m_input->getInput()->setRumble(unk3, unk1, unk2, flag);
}

void ftManager::setControllerRumbleAll(int unk1, int unk2, u32 isOn, int unk3) {
    u8 flag = 0;
    if (isOn == 1) {
        flag |= 1;
    }
    int count = getEntries(this).size();
    for (int i = 0; i < count; i++) {
        ftEntry* entry = getEntries(this).at(i);
        if (!entry->unk11_02) {
            entry->m_input->getInput()->setRumble(unk3, unk1, unk2, flag);
        }
    }
}

void ftManager::stopControllerRumbleAll(int unk1, int unk2) {
    int count = getEntries(this).size();
    for (int i = 0; i < count; i++) {
        getEntries(this).at(i)->m_input->getInput()->stopRumble(unk2, unk1);
    }
}

void ftManager::createFighter(int entryId) {
    ftEntry* entry = m_entryManager->getEntity(entryId);
    entry->createInstance();
    entry->unkC = 0;
}

static inline bool isTeamBattle(const ftManager* manager) {
    return manager->m_isTeams;
}

// True when a result entry of the given character kind exists that did not finish as a winner (in team battles: not on the winning team).
bool ftManager::isExistLoseFighterResult(int, int kind) const {
    gmPlayerResultInfo* player;
    int i;
    gmResultInfo* info = g_GameGlobal->m_resultInfo;
    for (i = 0; i < 7; i++) {
        player = &info->m_playersResultInfo[i];
        if (isTeamBattle(this) == true) {
            if (player->m_state != 3) {
                if (*reinterpret_cast<u8*>(player) == kind) {
                    if (player->m_teamNo != reinterpret_cast<u8*>(info)[0x1E]) {
                        return true;
                    }
                }
            }
        } else {
            if (player->m_state != 3) {
                if (*reinterpret_cast<u8*>(player) == kind) {
                    return true;
                }
            }
        }
    }
    return false;
}

// Horizontal offset of a fighter from the camera target.
float ftManager::getFighterScreenX(int entryId, int instanceIndex) const {
    Fighter* fighter = getFighter(entryId, instanceIndex);
    Vec3f pos = soExternalValueAccesser::getPrevRoughPos(fighter);
    float cameraX = gfCameraManager::getManager()->getCamera(0)->m_targetPos.m_x;
    return pos.m_x - cameraX;
}

// HYPOTHESIS: the loupe arrow is shown while the fighter is clipped out of view on one side only
bool ftManager::isDispLoupeArrow(int entryId, int instanceIndex) const {
    u32 clipOut = soExternalValueAccesser::getClipOutStatus(getFighter(entryId, instanceIndex));
    bool result = false;
    if (clipOut & 1) {
        if (!(clipOut & 2)) {
            result = true;
        }
    }
    return result;
}

// How far an entry is behind the best other entry: by stock in stock matches, by points (KOs minus falls, suicides not counted) otherwise.
int ftManager::getBeatPointDiffFromTop(int entryId) const {
    int top;
    int own;
    if (m_gameRule == 1) {
        top = 0;
        own = 0;
        int count = getEntries(this).size();
        for (int i = 0; i < count; i++) {
            ftEntry* entry = getEntries(this).at(i);
            int stock = entry->m_owner->getStockCount();
            if (entryId != entry->m_entryId) {
                if (top < stock) {
                    top = stock;
                }
            } else {
                own = stock;
            }
        }
        return top - own;
    }
    top = 0;
    own = 0;
    int count = getEntries(this).size();
    for (int i = 0; i < count; i++) {
        ftEntry* entry = getEntries(this).at(i);
        ftOwner* owner = entry->m_owner;
        int lost = owner->getDeadCount() - static_cast<u16>(owner->getSuicideCount());
        int score = entry->m_owner->getBeatCountTotal() - lost;
        if (entryId != entry->m_entryId) {
            if (top < score) {
                top = score;
            }
        } else {
            own = score;
        }
    }
    return top - own;
}

void ftManager::processBegin() {
    if (unk6b != 0) {
        unk6b--;
    }
    if (g_GameGlobal->isJustGameFrame() == true) {
        g_ftSlotManager->process();
        m_entryManager->process();
        int count = getEntries(this).size();
        for (int i = 0; i < count; i++) {
            getEntries(this).at(i)->m_owner->process();
        }
    }
}

// While the input event is running, tells the observers whenever an entry's controller changed.
void ftManager::processUpdate() {
    if (g_GameGlobal->isJustGameFrame() == true) {
        if (unk6c_10 == true) {
            int count = getEntries(this).size();
            for (int i = 0; i < count; i++) {
                ftEntry* entry = getEntries(this).at(i);
                ftInputController* controller = entry->m_input->getInput();
                u64 buttons1;
                u64 buttons0;
                buttons0 = controller->getButtons0();
                buttons1 = controller->getButtons1();
                ftOwner* owner = entry->m_owner;
                if (owner->sameCheckController(controller->getControllerKind(), &buttons1, &buttons0) == false) {
                    u64 buttons1b;
                    u64 buttons0b;
                    buttons0b = controller->getButtons0();
                    buttons1b = controller->getButtons1();
                    owner = entry->m_owner;
                    owner->setController(controller->getControllerKind(), &buttons1b, &buttons0b);
                    ftOutsideEventPresenter presenter(m_eventManageModule.getManageId(), entry->m_entryId);
                    presenter.notifyOutsideEventOnInput();
                }
            }
        }
    }
}

void ftManager::startInputEvent() {
    int count = getEntries(this).size();
    for (int i = 0; i < count; i++) {
        ftEntry* entry = getEntries(this).at(i);
        ftInputController* controller = entry->m_input->getInput();
        u64 buttons1;
        u64 buttons0;
        buttons0 = controller->getButtons0();
        buttons1 = controller->getButtons1();
        ftOwner* owner = entry->m_owner;
        owner->setController(controller->getControllerKind(), &buttons1, &buttons0);
    }
    unk6c_10 = true;
}
