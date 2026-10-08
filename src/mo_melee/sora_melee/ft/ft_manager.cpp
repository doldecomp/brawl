// ftManager: the fighter manager. It owns the fighter entries (ftEntryManager) and resource slots (ftSlotManager) and
// is the single entry point the rest of the game uses to start, query and affect fighters.
#include <ft/ft_manager.h>
#include <ft/ft_common_data_accesser.h>
#include <ft/ft_external_value_accesser.h>
#include <gf/gf_task.h>
#include <gf/gf_task_scheduler.h>
#include <it/it_manager.h>
#include <mu/menu.h>
#include <so/so_external_value_accesser.h>

// HYPOTHESIS: the structure behind ftManager::m_dataProvider; only the flag read by isUseCompressedMode is known.
struct ftManagerSystemData {
    char _0x0[0x10A0];
    u8 m_isUseCompressedMode;
};

// Evaluated at each use: the entry manager pointer is reloaded after every call in a loop.
static inline soArray<ftEntry*>& getEntries(const ftManager* manager) {
    return manager->m_entryManager->m_entryArrayVector;
}

static inline ftManagerSystemData* getSystemData(const ftManager* manager) {
    return static_cast<ftManagerSystemData*>(manager->m_dataProvider);
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
    for (int i = 0; i < g_ftSlotManager->m_slotCount; i++) {
        g_ftSlotManager->m_slots[i].remove(0xFF, 0x7000, 0);
    }
}

void ftManager::removeResourceAll() {
    for (int i = 0; i < g_ftSlotManager->m_slotCount; i++) {
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
    }
    return entryId;
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
int ftManager::getRealRebirthEntryId(int entryId) const {
    if (m_gameRule == 1) {
        ftEntry* entry = m_entryManager->getEntity(entryId);
        int partnerId = entry->m_heartSwapEntryId;
        if (partnerId != -1) {
            if (m_entryManager->getEntity(partnerId)->unk11_02 == true) {
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
    soArray<ftEntry*>& entries = m_entryManager->m_entryArrayVector;
    int count = entries.size();
    for (int i = 0; i < count; i++) {
        ftEntry* entry = entries.at(i);
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
    soArray<ftEntry*>& entries = m_entryManager->m_entryArrayVector;
    int count = entries.size();
    for (int i = 0; i < count; i++) {
        entries.at(i)->m_input->setWhole(status);
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
    for (int i = 0; i < g_ftSlotManager->m_slotCount; i++) {
        if (g_ftSlotManager->m_slots[i].isLoaded(0x7000) == true) {
            return true;
        }
    }
    soArray<ftEntry*>& entries = m_entryManager->m_entryArrayVector;
    int count = entries.size();
    for (int i = 0; i < count; i++) {
        if (entries.at(i)->isProcessTechnique() == true) {
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
    return m_entryManager->getEntity(entryId)->m_activeInstanceIndex;
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
    return *reinterpret_cast<u8*>(reinterpret_cast<u8*>(m_entryManager) + 0x3C);
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
    int count = getEntries(this).size();
    for (int i = 0; i < count; i++) {
        if ((u8)getEntries(this).at(i)->isExistFighter(taskId) != 0xFF) {
            int entryId = getEntries(this).at(i)->m_entryId;
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
